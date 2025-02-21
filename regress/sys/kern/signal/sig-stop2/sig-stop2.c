/*	$OpenBSD: sig-stop2.c,v 1.1 2024/10/07 14:01:12 claudio Exp $	*/
/*
 *	Written by Artur Grabowski <art@openbsd.org> 2007 Public Domain.
 *	Written by Claudio Jeker <claudio@openbsd.org> 2024 Public Domain.
 */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <err.h>
#include <signal.h>
#include <pthread.h>

#define	THREAD_COUNT	4

volatile sig_atomic_t tstp_count, cont_count;
pid_t child;

static void
tstp_handler(int sig)
{
	tstp_count++;
	dprintf(STDERR_FILENO, "SIGTSTP\n");
	kill(getpid(), SIGSTOP);
}

static void
cont_handler(int sig)
{
	dprintf(STDERR_FILENO, "SIGCONT\n");
	cont_count++;
}

static void
alrm_handler(int sig)
{
	kill(child, SIGKILL);
	dprintf(STDERR_FILENO, "timeout\n");
	_exit(2);
}


static void *
thread(void *arg)
{
	struct timespec ts = { .tv_sec = 2 };

	while (nanosleep(&ts, &ts) != 0)
		;

	return NULL;
}

static int
child_main(void)
{
	pthread_t self, pthread[THREAD_COUNT];
	sigset_t set;
	int i, r;

	signal(SIGTSTP, tstp_handler);
	signal(SIGCONT, cont_handler);

	sigemptyset(&set);
	sigaddset(&set, SIGTSTP);
	sigaddset(&set, SIGCONT);

	self = pthread_self();
	for (i = 0; i < THREAD_COUNT; i++) {
		if ((r = pthread_create(&pthread[i], NULL, thread, NULL))) {
			warnc(r, "could not create thread");
			pthread[i] = self;
		}
	}

	sigprocmask(SIG_BLOCK, &set, NULL);

	for (i = 0; i < THREAD_COUNT; i++) {
		if (!pthread_equal(pthread[i], self) &&
		    (r = pthread_join(pthread[i], NULL)))
			warnc(r, "could not join thread");
	}

	printf("#tstp = %d #cont = %d\n", tstp_count, cont_count);

	return !(tstp_count == 1 && cont_count == 1);
}

int
main(int argc, char **argv)
{
	struct timespec ts = { .tv_nsec = 200 * 1000 * 1000 };
	int status;

	switch((child = fork())) {
	case -1:
		err(1, "fork");
	case 0:
		exit(child_main());
	default:
		break;
	}

	signal(SIGALRM, alrm_handler);
	alarm(5);

	nanosleep(&ts, NULL);

	if (kill(child, SIGTSTP) == -1)
		err(1, "kill");

	if (waitpid(child, &status, WCONTINUED|WUNTRACED) <= 0)
		err(1, "waitpid");

	nanosleep(&ts, NULL);

	if (kill(child, SIGCONT) == -1)
		err(1, "kill");

	if (waitpid(child, &status, WCONTINUED|WUNTRACED) <= 0)
		err(1, "waitpid");

	nanosleep(&ts, NULL);

	if (waitpid(child, &status, 0) <= 0)
		err(1, "waitpid");

	if (!WIFEXITED(status))
		err(1, "bad status: %d", status);

	return WEXITSTATUS(status);
}
