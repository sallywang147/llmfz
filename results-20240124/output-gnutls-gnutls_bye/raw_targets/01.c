 #include <assert.h>
#include <stdint.h>

#include <gnutls/gnutls.h>
#include <gnutls/x509.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	gnutls_session_t session;
	int ret;

	ret = gnutls_init(&session, GNUTLS_CLIENT);
	assert(ret == 0);

	ret = gnutls_bye(session, GNUTLS_SHUT_RDWR);
	assert(ret >= 0);

	gnutls_deinit(session);
	return 0;
}