/*	$OpenBSD: library_mquery.c,v 1.76 2024/04/05 13:51:47 deraadt Exp $ */

/*
 * Copyright (c) 2002 Dale Rahn
 * Copyright (c) 1998 Per Fogelstrom, Opsycon AB
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#define _DYN_LOADER

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "syscall.h"
#include "util.h"
#include "archdep.h"
#include "resolve.h"
#include "sod.h"

#define PFLAGS(X) ((((X) & PF_R) ? PROT_READ : 0) | \
		   (((X) & PF_W) ? PROT_WRITE : 0) | \
		   (((X) & PF_X) ? PROT_EXEC : 0))

void
_dl_load_list_free(struct load_list *load_list)
{
	struct load_list *next;
	Elf_Addr align = _dl_pagesz - 1;

	while (load_list != NULL) {
		if (load_list->start != NULL)
			_dl_munmap(load_list->start,
			    ((load_list->size) + align) & ~align);
		next = load_list->next;
		_dl_free(load_list);
		load_list = next;
	}
}

void
_dl_unload_shlib(elf_object_t *object)
{
	struct dep_node *n;
	elf_object_t *load_object = object->load_object;

	/*
	 * If our load object has become unreferenced then we lost the
	 * last group reference to it, so the entire group should be taken
	 * down.  The current object is somewhere below load_object in
	 * the child_vec tree, so it'll get cleaned up by the recursion.
	 * That means we can just switch here to the load object.
	 */
	if (load_object != object && OBJECT_REF_CNT(load_object) == 0 &&
	    (load_object->status & STAT_UNLOADED) == 0) {
		DL_DEB(("unload_shlib switched from %s to %s\n",
		    object->load_name, load_object->load_name));
		object = load_object;
		goto unload;
	}

	DL_DEB(("unload_shlib called on %s\n", object->load_name));
	if (OBJECT_REF_CNT(object) == 0 &&
	    (object->status & STAT_UNLOADED) == 0) {
		struct object_vector vec;
		int i;
unload:
		object->status |= STAT_UNLOADED;
		for (vec = object->child_vec, i = 0; i < vec.len; i++)
			_dl_unload_shlib(vec.vec[i]);
		TAILQ_FOREACH(n, &object->grpref_list, next_sib)
			_dl_unload_shlib(n->data);
		DL_DEB(("unload_shlib unloading on %s\n", object->load_name));
		_dl_load_list_free(object->load_list);
		_dl_remove_object(object);
	}
}

elf_object_t *
_dl_tryload_shlib(const char *libname, int type, int flags, int nodelete)
{
	struct range_vector imut, mut;
	int libfile, libc = -1, i;
	struct load_list *ld, *lowld = NULL;
	elf_object_t *object;
	Elf_Dyn *dynp = NULL;
	Elf_Ehdr *ehdr;
	Elf_Phdr *phdp, *ptls = NULL;
	Elf_Phdr *syscall_phdp = NULL;
	Elf_Addr load_end = 0;
	Elf_Addr align = _dl_pagesz - 1, off, size;
	Elf_Addr relro_addr = 0, relro_size = 0;
	struct stat sb;
	char hbuf[4096], *exec_start;
	size_t exec_size;

#define powerof2(x) ((((x) - 1) & (x)) == 0)
#define ROUND_PG(x) (((x) + align) & ~(align))
#define TRUNC_PG(x) ((x) & ~(align))

	libfile = _dl_open(libname, O_RDONLY | O_CLOEXEC);
	if (libfile < 0) {
		_dl_errno = DL_CANT_OPEN;
		return(0);
	}

	if (_dl_fstat(libfile, &sb) < 0) {
		_dl_errno = DL_CANT_OPEN;
		return(0);
	}

	for (object = _dl_objects; object != NULL; object = object->next) {
		if (object->dev == sb.st_dev &&
		    object->inode == sb.st_ino) {
			_dl_close(libfile);
			_dl_handle_already_loaded(object, flags);
			return(object);
		}
	}
	if (flags & DF_1_NOOPEN) {
		_dl_close(libfile);
		return NULL;
	}

	_dl_read(libfile, hbuf, sizeof(hbuf));
	ehdr = (Elf_Ehdr *)hbuf;
	if (ehdr->e_ident[0] != ELFMAG0  || ehdr->e_ident[1] != ELFMAG1 ||
	    ehdr->e_ident[2] != ELFMAG2 || ehdr->e_ident[3] != ELFMAG3 ||
	    ehdr->e_type != ET_DYN || ehdr->e_machine != MACHID) {
		_dl_close(libfile);
		_dl_errno = DL_NOT_ELF;
		return(0);
	}

	/* Insertion sort */
#define LDLIST_INSERT(ld) do { \
	struct load_list **_ld; \
	for (_ld = &lowld; *_ld != NULL; _ld = &(*_ld)->next) \
		if ((*_ld)->moff > ld->moff) \
			break; \
	ld->next = *_ld; \
	*_ld = ld; \
} while (0)
	/*
	 *  Alright, we might have a winner!
	 *  Figure out how much VM space we need and set up the load
	 *  list that we'll use to find free VM space.
	 */
	phdp = (Elf_Phdr *)(hbuf + ehdr->e_phoff);
	for (i = 0; i < ehdr->e_phnum; i++, phdp++) {
		if (phdp->p_align > 1 && !powerof2(phdp->p_align)) {
			_dl_printf("%s: ld.so invalid ELF input %s.\n",
			    __progname, libname);
			_dl_close(libfile);
			_dl_errno = DL_CANT_MMAP;
			return(0);
		}

		switch (phdp->p_type) {
		case PT_LOAD:
			off = (phdp->p_vaddr & align);
			size = off + phdp->p_filesz;

			if (size != 0) {
				ld = _dl_malloc(sizeof(struct load_list));
				if (ld == NULL)
					_dl_oom();
				ld->start = NULL;
				ld->size = size;
				ld->moff = TRUNC_PG(phdp->p_vaddr);
				ld->foff = TRUNC_PG(phdp->p_offset);
				ld->prot = PFLAGS(phdp->p_flags);
				LDLIST_INSERT(ld);
			}

			if ((PFLAGS(phdp->p_flags) & PROT_WRITE) == 0 ||
			    ROUND_PG(size) == ROUND_PG(off + phdp->p_memsz))
				break;
			/* This phdr has a zfod section */
			ld = _dl_calloc(1, sizeof(struct load_list));
			if (ld == NULL)
				_dl_oom();
			ld->start = NULL;
			ld->size = ROUND_PG(off + phdp->p_memsz) -
			    ROUND_PG(size);
			ld->moff = TRUNC_PG(phdp->p_vaddr) +
			    ROUND_PG(size);
			ld->foff = -1;
			ld->prot = PFLAGS(phdp->p_flags);
			LDLIST_INSERT(ld);
			break;
		case PT_DYNAMIC:
			dynp = (Elf_Dyn *)phdp->p_vaddr;
			break;
		case PT_TLS:
			if (phdp->p_filesz > phdp->p_memsz) {
				_dl_printf("%s: invalid tls data in %s.\n",
				    __progname, libname);
				_dl_close(libfile);
				_dl_errno = DL_CANT_LOAD_OBJ;
				return(0);
			}
			if (!_dl_tib_static_done) {
				ptls = phdp;
				break;
			}
			_dl_printf("%s: unsupported TLS program header in %s\n",
			    __progname, libname);
			_dl_close(libfile);
			_dl_errno = DL_CANT_LOAD_OBJ;
			return(0);
		default:
			break;
		}
	}

#define LOFF ((Elf_Addr)lowld->start - lowld->moff)

retry:
	_dl_memset(&mut, 0, sizeof mut);
	_dl_memset(&imut, 0, sizeof imut);
	exec_start = NULL;
	exec_size = 0;
	for (ld = lowld; ld != NULL; ld = ld->next) {
		off_t foff;
		int fd, flags;
		void *res;

		flags = MAP_PRIVATE;

		if (ld->foff < 0) {
			fd = -1;
			foff = 0;
			flags |= MAP_ANON;
		} else {
			fd = libfile;
			foff = ld->foff;
		}

		if (ld == lowld) {
			/*
			 * Add PROT_EXEC to force the first allocation in
			 * EXEC region unless it is writable.
			 */
			int exec = (ld->prot & PROT_WRITE) ? 0 : PROT_EXEC;
			if (exec && lowld->start == NULL)
				lowld->start = _dl_exec_hint;
			res = _dl_mquery((void *)(LOFF + ld->moff),
			    ROUND_PG(ld->size), ld->prot | exec, flags,
			    fd, foff);
			if (_dl_mmap_error(res))
				goto fail;
			lowld->start = res;
		}

		res = _dl_mmap((void *)(LOFF + ld->moff), ROUND_PG(ld->size),
		    ld->prot, flags | MAP_FIXED | __MAP_NOREPLACE, fd, foff);
		if (_dl_mmap_error(res)) {
			struct load_list *ll;

			/* Unmap any mappings that we did get in. */
			for (ll = lowld; ll != NULL && ll != ld;
			     ll = ll->next) {
				_dl_munmap(ll->start, ROUND_PG(ll->size));
			}

			lowld->start += ROUND_PG(ld->size);
			goto retry;
		}

		if ((ld->prot & PROT_EXEC) && exec_start == NULL) {
			exec_start = (void *)(LOFF + ld->moff);
			exec_size = ROUND_PG(ld->size);
		}

		/* Entire mapping can become immutable, minus exceptions chosen later */
		_dl_push_range_size(&imut, LOFF + ld->moff, ROUND_PG(ld->size));

		ld->start = res;
	}

	for (ld = lowld; ld != NULL; ld = ld->next) {
		/* Zero out everything past the EOF */
		if ((ld->prot & PROT_WRITE) != 0 && (ld->size & align) != 0)
			_dl_memset((char *)ld->start + ld->size, 0,
			    _dl_pagesz - (ld->size & align));
		load_end = (Elf_Addr)ld->start + ROUND_PG(ld->size);
	}

	phdp = (Elf_Phdr *)(hbuf + ehdr->e_phoff);
	for (i = 0; i < ehdr->e_phnum; i++, phdp++) {
		switch (phdp->p_type) {
		case PT_OPENBSD_RANDOMIZE:
			_dl_arc4randombuf((char *)(phdp->p_vaddr + LOFF),
			    phdp->p_memsz);
			break;
		case PT_GNU_RELRO:
			relro_addr = phdp->p_vaddr + LOFF;
			relro_size = phdp->p_memsz;
			_dl_push_range_size(&mut, relro_addr, relro_size);
			break;
		case PT_OPENBSD_MUTABLE:
			_dl_push_range_size(&mut, phdp->p_vaddr + LOFF,
			    phdp->p_memsz);
			break;
		case PT_OPENBSD_SYSCALLS:
			syscall_phdp = phdp;
			break;
		}
	}

	libc = _dl_islibc(dynp, LOFF);
	if (libc && syscall_phdp)
		_dl_pin(libfile, syscall_phdp, lowld->start,
		    (size_t)((exec_start + exec_size) - LOFF),
		    exec_start, exec_size);
	_dl_close(libfile);

	dynp = (Elf_Dyn *)((unsigned long)dynp + LOFF);
	object = _dl_finalize_object(libname, dynp,
	    (Elf_Phdr *)((char *)lowld->start + ehdr->e_phoff), ehdr->e_phnum,
	    type, (Elf_Addr)lowld->start, LOFF);
	if (object) {
		object->load_size = (Elf_Addr)load_end - (Elf_Addr)lowld->start;
		object->load_list = lowld;
		/* set inode, dev from stat info */
		object->dev = sb.st_dev;
		object->inode = sb.st_ino;
		object->obj_flags |= flags;
		object->nodelete = nodelete;
		object->relro_addr = relro_addr;
		object->relro_size = relro_size;
		object->islibc = libc;
		_dl_set_sod(object->load_name, &object->sod);
		if (ptls != NULL && ptls->p_memsz)
			_dl_set_tls(object, ptls, (Elf_Addr)lowld->start,
			    libname);
		_dl_bcopy(&mut, &object->mut, sizeof mut);
		_dl_bcopy(&imut, &object->imut, sizeof imut);
	} else {
		_dl_load_list_free(lowld);
	}
	return(object);
fail:
	_dl_printf("%s: ld.so mmap failed mapping %s.\n", __progname, libname);
	_dl_close(libfile);
	_dl_errno = DL_CANT_MMAP;
	_dl_load_list_free(lowld);
	return(0);
}
