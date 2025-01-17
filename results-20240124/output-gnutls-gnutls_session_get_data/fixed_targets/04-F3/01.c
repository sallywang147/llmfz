#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <gnutls/gnutls.h>

extern "C" {
#include "fuzzer.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	gnutls_session_t session;
	char *buf;
	size_t buf_size;

	gnutls_global_init();

	gnutls_init(&session, GNUTLS_CLIENT);
	gnutls_session_set_ptr(session, GNUTLS_SSL_DATA_PENDING, (void *)1);

	buf = malloc(size);
	assert(buf);

	int ret = gnutls_session_get_data(session, buf, &buf_size);
	assert(ret == GNUTLS_E_AGAIN);

	free(buf);
	gnutls_deinit(session);
	gnutls_global_deinit();

	return 0;
}