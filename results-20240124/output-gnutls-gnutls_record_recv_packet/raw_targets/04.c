 #include <stddef.h>
#include <stdint.h>
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

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	struct gnutls_session_int *session;
	struct mbuffer_st *mbuf;
	size_t ret;

	gnutls_global_set_time_function(mytime);

	session = gnutls_session_new(GNUTLS_SERVER);
	if (!session)
		return 0;

	ret = gnutls_record_recv_packet(session, &mbuf);
	if (ret != 0)
		goto fail;

	gnutls_session_free(session);
	return 0;

fail:
	gnutls_session_free(session);
	return 0;
}