#include <assert.h>
#include <stdint.h>
#include <stddef.h>

#include <gnutls/gnutls.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "fuzzer.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	gnutls_session_t session;
	gnutls_datum_t data_out;

	gnutls_global_init();
	gnutls_init(&session, GNUTLS_CLIENT);
	gnutls_session_set_data(session, (void *)data, size);

	gnutls_session_get_data2(session, &data_out);

	gnutls_deinit(session);
	gnutls_global_deinit();

	return 0;
}