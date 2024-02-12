#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fuzzer.h"
#include "gnutls/gnutls.h"

static time_t mytime(time_t *t)
{
	time_t then = 1553835274;
	if (t)
		*t = then;

	return then;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
	gnutls_datum_t out;
	gnutls_session_t session;

	gnutls_global_set_time_function(mytime);

	gnutls_init(&session, GNUTLS_SERVER);
	gnutls_session_set_data(session, data, size);

	int ret = gnutls_session_get_data2(session, &out);
	if (ret < 0)
		return 0;

	gnutls_deinit(session);

	return 0;
}