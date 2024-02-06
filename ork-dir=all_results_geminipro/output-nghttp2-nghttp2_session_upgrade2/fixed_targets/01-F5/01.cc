#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "nghttp2_session.h"
#include <string.h>
#include "nghttp2_test_helper.h"
}

void check_session_upgrade2(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  int rv;
  nghttp2_mem *mem;
  char *host;
  size_t hostlen;
  int port;
  char *path;
  size_t pathlen;

  mem = nghttp2_mem_default();
  session = nghttp2_session_new(mem, NULL, NULL);
  host = data_provider->ConsumeRandomLengthString(100);
  hostlen = strlen(host);
  port = data_provider->ConsumeIntegral<int>();
  path = data_provider->ConsumeRandomLengthString(100);
  pathlen = strlen(path);

  /* Perform a set of operations with the fuzz data */
  rv = nghttp2_session_upgrade2(session, host, hostlen, port, path, NULL);

  /* Cleanup */
  nghttp2_session_del(session);
  nghttp2_mem_free(mem);  // Free the memory allocated by nghttp2_mem_default()
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_session_upgrade2(&data_provider);
  return 0;
}