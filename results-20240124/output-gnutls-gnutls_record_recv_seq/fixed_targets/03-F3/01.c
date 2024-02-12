#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include <gnutls/gnutls.h>
#include <gnutls/record.h>

#include "fuzzer.h"

#include "malloca.h"
#include "stdckdint.h"

static time_t mytime(time_t *t)
{
	time_t then = 1553835274;
	if (t)
		*t = then;

	return then;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	gnutls_session_int session;
	size_t ret;

	gnutls_global_set_time_function(mytime);

	ret = gnutls_record_recv_seq(&session, (char *)data, size, NULL);
	assert(ret < 0);

	return 0;
}