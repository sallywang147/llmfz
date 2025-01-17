#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <gnutls/gnutls.h>
#include <gnutls/x509.h>
#include <gnutls/crypto.h>

#include "fuzzer.h"

extern "C" {
#include <time.h>
}

static time_t mytime(time_t *t)
{
	time_t then = 1553835274;
	if (t)
		*t = then;

	return then;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	gnutls_session_t session;
	gnutls_datum_t raw;
	gnutls_x509_crt_t ca_crt;
	gnutls_x509_privkey_t ca_key;
	size_t recv_size;
	int ret;

	gnutls_global_set_time_function(mytime);

	ret = gnutls_certificate_allocate_credentials(&ca_crt, &ca_key);
	assert(ret >= 0);

	gnutls_certificate_set_x509_key(ca_crt, ca_key);

	ret = gnutls_init(&session, GNUTLS_SERVER);
	assert(ret >= 0);

	gnutls_priority_set_direct(session, "NORMAL", NULL);

	ret = gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, ca_crt);
	assert(ret >= 0);

	ret = gnutls_handshake(session);
	assert(ret >= 0);

	raw.data = (unsigned char *)data;
	raw.size = size;

	recv_size = gnutls_record_recv_seq(session, NULL, 0, NULL);
	assert(recv_size >= 0);

	gnutls_deinit(session);

	gnutls_certificate_free_credentials(ca_crt);

	return 0;
}