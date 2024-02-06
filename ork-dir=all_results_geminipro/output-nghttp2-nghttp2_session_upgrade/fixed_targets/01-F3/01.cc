#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "nghttp2_session.h"
#include <string.h>
#include <nghttp2_test_helper.h>

void check_session_upgrade(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  int rv;
  char *path;
  size_t pathlen;
  char *settings;
  size_t settingslen;

  session = nghttp2_session_new();
  if (session == NULL) {
    return;
  }

  pathlen = data_provider->ConsumeIntegralInRange(0, 1024);
  path = (char *)data_provider->ConsumeBytes(pathlen).data();

  settingslen = data_provider->ConsumeIntegralInRange(0, 1024);
  settings = (char *)data_provider->ConsumeBytes(settingslen).data();

  /* Perform a set of operations with the fuzz data */
  rv = nghttp2_session_upgrade2(session, path, pathlen, settings, settingslen, NULL);

  /* Cleanup */
  nghttp2_session_del(session);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_session_upgrade(&data_provider);
  return 0;
}

} // extern C