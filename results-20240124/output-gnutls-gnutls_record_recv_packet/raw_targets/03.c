 #include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include <gnutls/gnutls.h>
#include <gnutls/mbuf.h>
#include <gnutls/record.h>

#include "fuzzer.h"

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
	struct mbuffer_st *mbuf;
	size_t ret;

	gnutls_global_set_time_function(mytime);

	ret = gnutls_init(&session, GNUTLS_CLIENT);
	assert(ret >= 0);

	ret = gnutls_record_recv_packet(session, &mbuf);
	assert(ret < 0);

	gnutls_deinit(session);

	return 0;
}