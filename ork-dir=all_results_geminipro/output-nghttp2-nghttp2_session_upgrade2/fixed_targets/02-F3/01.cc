#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <nghttp2/nghttp2.h>
#include <string.h>

#define BUFFER_SIZE 1024

void check_nghttp2_session_upgrade2(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  char *buffer;
  size_t buffer_size;
  int rv;
  char *settings_payload;

  session = nghttp2_session_client_new();
  buffer = data_provider->ConsumeBytes<char>(BUFFER_SIZE);
  buffer_size = data_provider->ConsumeIntegralInRange(0, BUFFER_SIZE);
  settings_payload = data_provider->ConsumeBytes<char>(BUFFER_SIZE);

  /* Perform a set of operations with the fuzz data */
  rv = nghttp2_session_upgrade2(session, buffer, buffer_size, NGHTTP2_PROTO_HTTP2, settings_payload);
  if (rv == 0) {
    nghttp2_session_del(session);
  }

  /* Cleanup */
  free(buffer);
  free(settings_payload);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_nghttp2_session_upgrade2(&data_provider);
  return 0;
}

} // extern "C"