#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "fuzzer.h"

#include <gnutls/gnutls.h>
#include <gnutls/record.h>

extern "C" {
#include <stdbool.h>
}

size_t gnutls_record_recv_seq(struct gnutls_session_int *session, char *buf,
                             size_t buf_size, char *err)
{
	return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	gnutls_session_int session;
	char buf[1024];
	char err[1024];

	memset(&session, 0, sizeof(session));
	size_t ret = gnutls_record_recv_seq(&session, buf, sizeof(buf), err);
	(void)ret;
	return 0;
}