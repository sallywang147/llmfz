#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "gnutls/gnutls.h"

extern "C" {
#include <malloc.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  gnutls_session_t session;
  gnutls_session_init(&session);

  char *buf = (char *)malloc(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  size_t len = stream.ConsumeIntegralInRange<size_t>(0, 1024);

  gnutls_session_get_data(session, buf, &len);

  free(buf);
  gnutls_session_deinit(session);

  return 0;
}