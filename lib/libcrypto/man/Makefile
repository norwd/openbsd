# $OpenBSD: Makefile,v 1.312 2025/07/17 10:31:50 schwarze Exp $

.include <bsd.own.mk>

MAN=	\
	ACCESS_DESCRIPTION_new.3 \
	AES_encrypt.3 \
	ASIdentifiers_new.3 \
	ASN1_BIT_STRING_set.3 \
	ASN1_INTEGER_get.3 \
	ASN1_NULL_new.3 \
	ASN1_OBJECT_new.3 \
	ASN1_PRINTABLE_type.3 \
	ASN1_STRING_TABLE_get.3 \
	ASN1_STRING_length.3 \
	ASN1_STRING_new.3 \
	ASN1_STRING_print_ex.3 \
	ASN1_TIME_set.3 \
	ASN1_TYPE_get.3 \
	ASN1_UNIVERSALSTRING_to_string.3 \
	ASN1_generate_nconf.3 \
	ASN1_get_object.3 \
	ASN1_item_d2i.3 \
	ASN1_item_digest.3 \
	ASN1_item_new.3 \
	ASN1_item_pack.3 \
	ASN1_item_sign.3 \
	ASN1_item_verify.3 \
	ASN1_mbstring_copy.3 \
	ASN1_parse_dump.3 \
	ASN1_put_object.3 \
	ASRange_new.3 \
	AUTHORITY_KEYID_new.3 \
	BASIC_CONSTRAINTS_new.3 \
	BF_set_key.3 \
	BIO_accept.3 \
	BIO_ctrl.3 \
	BIO_dump.3 \
	BIO_dup_chain.3 \
	BIO_f_base64.3 \
	BIO_f_buffer.3 \
	BIO_f_cipher.3 \
	BIO_f_md.3 \
	BIO_f_null.3 \
	BIO_find_type.3 \
	BIO_get_data.3 \
	BIO_get_ex_new_index.3 \
	BIO_meth_new.3 \
	BIO_new.3 \
	BIO_new_CMS.3 \
	BIO_printf.3 \
	BIO_push.3 \
	BIO_read.3 \
	BIO_s_accept.3 \
	BIO_s_bio.3 \
	BIO_s_connect.3 \
	BIO_s_datagram.3 \
	BIO_s_fd.3 \
	BIO_s_file.3 \
	BIO_s_mem.3 \
	BIO_s_null.3 \
	BIO_s_socket.3 \
	BIO_set_callback.3 \
	BIO_should_retry.3 \
	BN_CTX_new.3 \
	BN_CTX_start.3 \
	BN_add.3 \
	BN_add_word.3 \
	BN_bn2bin.3 \
	BN_cmp.3 \
	BN_copy.3 \
	BN_generate_prime.3 \
	BN_get_rfc3526_prime_8192.3 \
	BN_kronecker.3 \
	BN_mod_inverse.3 \
	BN_mod_mul_montgomery.3 \
	BN_mod_sqrt.3 \
	BN_new.3 \
	BN_num_bytes.3 \
	BN_rand.3 \
	BN_set_bit.3 \
	BN_set_flags.3 \
	BN_set_negative.3 \
	BN_swap.3 \
	BN_zero.3 \
	BUF_MEM_new.3 \
	CMAC_Init.3 \
	CMS_ContentInfo_new.3 \
	CMS_add0_cert.3 \
	CMS_add1_recipient_cert.3 \
	CMS_add1_signer.3 \
	CMS_compress.3 \
	CMS_decrypt.3 \
	CMS_encrypt.3 \
	CMS_final.3 \
	CMS_get0_RecipientInfos.3 \
	CMS_get0_SignerInfos.3 \
	CMS_get0_type.3 \
	CMS_get1_ReceiptRequest.3 \
	CMS_sign.3 \
	CMS_sign_receipt.3 \
	CMS_signed_add1_attr.3 \
	CMS_uncompress.3 \
	CMS_verify.3 \
	CMS_verify_receipt.3 \
	CONF_modules_free.3 \
	CONF_modules_load_file.3 \
	CRYPTO_lock.3 \
	CRYPTO_memcmp.3 \
	CRYPTO_set_ex_data.3 \
	CRYPTO_set_mem_functions.3 \
	ChaCha.3 \
	DES_set_key.3 \
	DH_generate_key.3 \
	DH_generate_parameters.3 \
	DH_get0_pqg.3 \
	DH_get_ex_new_index.3 \
	DH_new.3 \
	DH_set_method.3 \
	DH_size.3 \
	DIST_POINT_new.3 \
	DSA_SIG_new.3 \
	DSA_do_sign.3 \
	DSA_dup_DH.3 \
	DSA_generate_key.3 \
	DSA_generate_parameters_ex.3 \
	DSA_get0_pqg.3 \
	DSA_get_ex_new_index.3 \
	DSA_meth_new.3 \
	DSA_new.3 \
	DSA_set_method.3 \
	DSA_sign.3 \
	DSA_size.3 \
	ECDH_compute_key.3 \
	ECDSA_SIG_new.3 \
	EC_GROUP_check.3 \
	EC_GROUP_get_curve_name.3 \
	EC_GROUP_new_by_curve_name.3 \
	EC_GROUP_new_curve_GFp.3 \
	EC_KEY_METHOD_new.3 \
	EC_KEY_new.3 \
	EC_POINT_add.3 \
	EC_POINT_get_affine_coordinates.3 \
	EC_POINT_new.3 \
	EC_POINT_point2oct.3 \
	ENGINE_new.3 \
	ERR.3 \
	ERR_GET_LIB.3 \
	ERR_asprintf_error_data.3 \
	ERR_clear_error.3 \
	ERR_error_string.3 \
	ERR_get_error.3 \
	ERR_load_crypto_strings.3 \
	ERR_load_strings.3 \
	ERR_print_errors.3 \
	ERR_put_error.3 \
	ERR_remove_state.3 \
	ERR_set_mark.3 \
	ESS_SIGNING_CERT_new.3 \
	EVP_AEAD_CTX_init.3 \
	EVP_BytesToKey.3 \
	EVP_CIPHER_CTX_ctrl.3 \
	EVP_CIPHER_CTX_get_cipher_data.3 \
	EVP_CIPHER_CTX_init.3 \
	EVP_CIPHER_CTX_set_flags.3 \
	EVP_CIPHER_do_all.3 \
	EVP_CIPHER_meth_new.3 \
	EVP_CIPHER_nid.3 \
	EVP_DigestInit.3 \
	EVP_DigestSignInit.3 \
	EVP_DigestVerifyInit.3 \
	EVP_EncodeInit.3 \
	EVP_EncryptInit.3 \
	EVP_MD_CTX_ctrl.3 \
	EVP_MD_nid.3 \
	EVP_OpenInit.3 \
	EVP_PKCS82PKEY.3 \
	EVP_PKEY_CTX_ctrl.3 \
	EVP_PKEY_CTX_get_operation.3 \
	EVP_PKEY_CTX_new.3 \
	EVP_PKEY_CTX_set_hkdf_md.3 \
	EVP_PKEY_CTX_set_tls1_prf_md.3 \
	EVP_PKEY_asn1_get_count.3 \
	EVP_PKEY_cmp.3 \
	EVP_PKEY_decrypt.3 \
	EVP_PKEY_derive.3 \
	EVP_PKEY_encrypt.3 \
	EVP_PKEY_get_default_digest_nid.3 \
	EVP_PKEY_keygen.3 \
	EVP_PKEY_new.3 \
	EVP_PKEY_new_CMAC_key.3 \
	EVP_PKEY_print_private.3 \
	EVP_PKEY_set1_RSA.3 \
	EVP_PKEY_sign.3 \
	EVP_PKEY_size.3 \
	EVP_PKEY_verify.3 \
	EVP_PKEY_verify_recover.3 \
	EVP_SealInit.3 \
	EVP_SignInit.3 \
	EVP_VerifyInit.3 \
	EVP_aes_128_cbc.3 \
	EVP_aes_128_ccm.3 \
	EVP_aes_128_gcm.3 \
	EVP_camellia_128_cbc.3 \
	EVP_chacha20.3 \
	EVP_des_cbc.3 \
	EVP_rc2_cbc.3 \
	EVP_rc4.3 \
	EVP_sha1.3 \
	EVP_sha3_224.3 \
	EVP_sm3.3 \
	EVP_sm4_cbc.3 \
	EXTENDED_KEY_USAGE_new.3 \
	GENERAL_NAME_new.3 \
	HMAC.3 \
	IPAddressRange_new.3 \
	MD5.3 \
	NAME_CONSTRAINTS_new.3 \
	OBJ_create.3 \
	OBJ_find_sigid_algs.3 \
	OBJ_nid2obj.3 \
	OCSP_CRLID_new.3 \
	OCSP_REQUEST_new.3 \
	OCSP_SERVICELOC_new.3 \
	OCSP_cert_to_id.3 \
	OCSP_request_add1_nonce.3 \
	OCSP_resp_find_status.3 \
	OCSP_response_status.3 \
	OCSP_sendreq_new.3 \
	OPENSSL_VERSION_NUMBER.3 \
	OPENSSL_cleanse.3 \
	OPENSSL_config.3 \
	OPENSSL_init_crypto.3 \
	OPENSSL_malloc.3 \
	OPENSSL_sk_new.3 \
	OpenSSL_add_all_algorithms.3 \
	PEM_ASN1_read.3 \
	PEM_X509_INFO_read_bio.3 \
	PEM_bytes_read_bio.3 \
	PEM_read.3 \
	PEM_read_bio_PrivateKey.3 \
	PEM_write_bio_CMS_stream.3 \
	PEM_write_bio_PKCS7_stream.3 \
	PKCS12_SAFEBAG_new.3 \
	PKCS12_create.3 \
	PKCS12_new.3 \
	PKCS12_newpass.3 \
	PKCS12_parse.3 \
	PKCS5_PBKDF2_HMAC.3 \
	PKCS7_add_attribute.3 \
	PKCS7_dataFinal.3 \
	PKCS7_dataInit.3 \
	PKCS7_decrypt.3 \
	PKCS7_encrypt.3 \
	PKCS7_final.3 \
	PKCS7_get_signer_info.3 \
	PKCS7_new.3 \
	PKCS7_set_content.3 \
	PKCS7_set_type.3 \
	PKCS7_sign.3 \
	PKCS7_sign_add_signer.3 \
	PKCS7_verify.3 \
	PKCS8_PRIV_KEY_INFO_new.3 \
	PKCS8_pkey_set0.3 \
	PKEY_USAGE_PERIOD_new.3 \
	POLICYINFO_new.3 \
	RAND_add.3 \
	RAND_bytes.3 \
	RAND_load_file.3 \
	RAND_set_rand_method.3 \
	RC2_encrypt.3 \
	RC4.3 \
	RIPEMD160.3 \
	RSA_PSS_PARAMS_new.3 \
	RSA_blinding_on.3 \
	RSA_check_key.3 \
	RSA_generate_key.3 \
	RSA_get0_key.3 \
	RSA_get_ex_new_index.3 \
	RSA_meth_new.3 \
	RSA_new.3 \
	RSA_padding_add_PKCS1_type_1.3 \
	RSA_pkey_ctx_ctrl.3 \
	RSA_print.3 \
	RSA_private_encrypt.3 \
	RSA_public_encrypt.3 \
	RSA_security_bits.3 \
	RSA_set_method.3 \
	RSA_sign.3 \
	RSA_sign_ASN1_OCTET_STRING.3 \
	RSA_size.3 \
	SHA1.3 \
	SMIME_crlf_copy.3 \
	SMIME_read_CMS.3 \
	SMIME_read_PKCS7.3 \
	SMIME_text.3 \
	SMIME_write_CMS.3 \
	SMIME_write_PKCS7.3 \
	STACK_OF.3 \
	TS_REQ_new.3 \
	UI_create_method.3 \
	UI_get_string_type.3 \
	UI_new.3 \
	X25519.3 \
	X509V3_EXT_get_nid.3 \
	X509V3_EXT_print.3 \
	X509V3_extensions_print.3 \
	X509V3_get_d2i.3 \
	X509V3_parse_list.3 \
	X509_ALGOR_dup.3 \
	X509_ATTRIBUTE_get0_object.3 \
	X509_ATTRIBUTE_new.3 \
	X509_ATTRIBUTE_set1_object.3 \
	X509_CINF_new.3 \
	X509_CRL_get0_by_serial.3 \
	X509_CRL_new.3 \
	X509_CRL_print.3 \
	X509_EXTENSION_set_object.3 \
	X509_INFO_new.3 \
	X509_LOOKUP_hash_dir.3 \
	X509_LOOKUP_new.3 \
	X509_NAME_ENTRY_get_object.3 \
	X509_NAME_add_entry_by_txt.3 \
	X509_NAME_get_index_by_NID.3 \
	X509_NAME_hash.3 \
	X509_NAME_new.3 \
	X509_NAME_print_ex.3 \
	X509_OBJECT_get0_X509.3 \
	X509_PUBKEY_new.3 \
	X509_PURPOSE_set.3 \
	X509_REQ_add1_attr.3 \
	X509_REQ_add_extensions.3 \
	X509_REQ_new.3 \
	X509_REQ_print_ex.3 \
	X509_REVOKED_new.3 \
	X509_SIG_get0.3 \
	X509_SIG_new.3 \
	X509_STORE_CTX_get_error.3 \
	X509_STORE_CTX_get_ex_new_index.3 \
	X509_STORE_CTX_new.3 \
	X509_STORE_CTX_set_flags.3 \
	X509_STORE_CTX_set_verify.3 \
	X509_STORE_CTX_set_verify_cb.3 \
	X509_STORE_get_by_subject.3 \
	X509_STORE_load_locations.3 \
	X509_STORE_new.3 \
	X509_STORE_set1_param.3 \
	X509_STORE_set_verify_cb_func.3 \
	X509_VERIFY_PARAM_new.3 \
	X509_VERIFY_PARAM_set_flags.3 \
	X509_add1_trust_object.3 \
	X509_check_ca.3 \
	X509_check_host.3 \
	X509_check_issued.3 \
	X509_check_private_key.3 \
	X509_check_purpose.3 \
	X509_cmp.3 \
	X509_cmp_time.3 \
	X509_digest.3 \
	X509_find_by_subject.3 \
	X509_get0_notBefore.3 \
	X509_get0_signature.3 \
	X509_get1_email.3 \
	X509_get_extension_flags.3 \
	X509_get_pubkey.3 \
	X509_get_pubkey_parameters.3 \
	X509_get_serialNumber.3 \
	X509_get_subject_name.3 \
	X509_get_version.3 \
	X509_keyid_set1.3 \
	X509_load_cert_file.3 \
	X509_new.3 \
	X509_ocspid_print.3 \
	X509_print_ex.3 \
	X509_sign.3 \
	X509_signature_dump.3 \
	X509_verify_cert.3 \
	X509v3_addr_add_inherit.3 \
	X509v3_addr_get_range.3 \
	X509v3_addr_inherits.3 \
	X509v3_addr_subset.3 \
	X509v3_addr_validate_path.3 \
	X509v3_asid_add_id_or_range.3 \
	X509v3_get_ext_by_NID.3 \
	a2d_ASN1_OBJECT.3 \
	a2i_ipadd.3 \
	crypto.3 \
	d2i_ASN1_NULL.3 \
	d2i_ASN1_OBJECT.3 \
	d2i_ASN1_OCTET_STRING.3 \
	d2i_ASN1_SEQUENCE_ANY.3 \
	d2i_AUTHORITY_KEYID.3 \
	d2i_BASIC_CONSTRAINTS.3 \
	d2i_CMS_ContentInfo.3 \
	d2i_DHparams.3 \
	d2i_DIST_POINT.3 \
	d2i_DSAPublicKey.3 \
	d2i_ECPKParameters.3 \
	d2i_ESS_SIGNING_CERT.3 \
	d2i_GENERAL_NAME.3 \
	d2i_OCSP_REQUEST.3 \
	d2i_OCSP_RESPONSE.3 \
	d2i_PKCS12.3 \
	d2i_PKCS7.3 \
	d2i_PKCS8PrivateKey_bio.3 \
	d2i_PKCS8_PRIV_KEY_INFO.3 \
	d2i_PKEY_USAGE_PERIOD.3 \
	d2i_POLICYINFO.3 \
	d2i_PrivateKey.3 \
	d2i_RSAPublicKey.3 \
	d2i_TS_REQ.3 \
	d2i_X509.3 \
	d2i_X509_ALGOR.3 \
	d2i_X509_ATTRIBUTE.3 \
	d2i_X509_CRL.3 \
	d2i_X509_EXTENSION.3 \
	d2i_X509_NAME.3 \
	d2i_X509_REQ.3 \
	d2i_X509_SIG.3 \
	des_read_pw.3 \
	evp.3 \
	i2a_ASN1_STRING.3 \
	i2d_CMS_bio_stream.3 \
	i2d_PKCS7_bio_stream.3 \
	lh_new.3 \
	openssl.cnf.5 \
	s2i_ASN1_INTEGER.3 \
	v2i_ASN1_BIT_STRING.3 \
	x509v3.cnf.5

all clean cleandir depend includes obj tags:

install: maninstall

.include <bsd.man.mk>
