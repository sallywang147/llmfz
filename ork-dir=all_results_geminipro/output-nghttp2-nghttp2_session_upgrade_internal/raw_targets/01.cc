#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "nghttp2_session.h"
#include "nghttp2_frame.h"
#include <string.h>

#include "nghttp2_test_helper.h"

void check_session_upgrade_internal(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  nghttp2_mem *mem;
  char *settings_payload;
  size_t settings_payloadlen;
  char *headers_payload;
  int rv;

  mem = nghttp2_mem_default();

  rv = nghttp2_session_client_new(&session, NULL, NULL, mem);
  if (rv != 0) {
    return;
  }

  /* Create a set of headers seeded with data from the fuzzer */
  settings_payloadlen = data_provider->ConsumeIntegralInRange(0, 1000);
  settings_payload = (char *)mem->malloc(settings_payloadlen, NULL);
  data_provider->ConsumeBytes(settings_payload, settings_payloadlen);

  headers_payloadlen = data_provider->ConsumeIntegralInRange(0, 1000);
  headers_payload = (char *)mem->malloc(headers_payloadlen, NULL);
  data_provider->ConsumeBytes(headers_payload, headers_payloadlen);

  /* Perform a set of operations with the fuzz data */
  rv = nghttp2_session_upgrade_internal(session, settings_payload, settings_payloadlen, headers_payload);

  /* Cleanup */
  nghttp2_session_del(session);
  mem->free(settings_payload, NULL);
  mem->free(headers_payload, NULL);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_session_upgrade_internal(&data_provider);
  return 0;
}

} // extern C