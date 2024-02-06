#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "nghttp2_session.h"
#include <string.h>

#include "nghttp2_test_helper.h"
}

void check_session_recv(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  nghttp2_mem *mem;
  int rv;
  size_t datalen;
  const uint8_t *data;

  mem = nghttp2_mem_default();
  session = nghttp2_session_new(mem, NULL, NULL);
  if (session == NULL) {
    return;
  }

  datalen = data_provider->ConsumeRemainingBytes(&data);

  /* Perform a set of operations with the fuzz data */
  rv = nghttp2_session_recv(session, data, datalen);

  /* Cleanup */
  nghttp2_session_del(session);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_session_recv(&data_provider);
  return 0;
}