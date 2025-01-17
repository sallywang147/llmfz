#include <assert.h>
#include <stdint.h>

#include <gnutls/gnutls.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer.h"

extern "C" {
#include <stdbool.h>
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
	gnutls_datum_t out;
	int ret;

	gnutls_global_set_time_function(mytime);

	ret = gnutls_init(&session, GNUTLS_CLIENT);
	assert(ret >= 0);

	ret = gnutls_session_set_data2(session, data, size);
	assert(ret >= 0);

	ret = gnutls_session_get_data2(session, &out);
	assert(ret >= 0);

	gnutls_deinit(session);
	return 0;
}