#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer.h"
#include "gnutls/gnutls.h"
#include "gnutls/gnutls_int.h"

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
	gnutls_session_int session;
	size_t rc;

	gnutls_global_set_time_function(mytime);

	memset(&session, 0, sizeof(session));

	rc = gnutls_record_recv_seq(&session, (char *)data, size, NULL);

	if (rc != 0)
		return 0;

	return 0;
}