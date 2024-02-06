#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "nghttp2_session.h"
#include <string.h>

#include "nghttp2_test_helper.h"

void check_session_upgrade(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  char *buffer;
  size_t buflen;
  char *settings;
  int rv;

  session = nghttp2_session_new();
  if (session == NULL) {
    return;
  }

  /* Create a set of headers seeded with data from the fuzzer */
  buflen = data_provider->ConsumeIntegralInRange(0, 1024);
  buffer = (char *)data_provider->ConsumeBytes<char>(buflen);

  buflen = data_provider->ConsumeIntegralInRange(0, 1024);
  settings = (char *)data_provider->ConsumeBytes<char>(buflen);

  /* Perform a set of operations with the fuzz data */
  rv = nghttp2_session_upgrade(session, buffer, buflen, settings);

  /* Cleanup */
  nghttp2_session_del(session);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_session_upgrade(&data_provider);
  return 0;
}

} // extern C