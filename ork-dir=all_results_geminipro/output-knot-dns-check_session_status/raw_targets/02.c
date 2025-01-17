#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_CLIENT);

  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> output_buffer(1024);

  size_t output_written = 0;
  // Initially, start by feeding the decoder more data.
  int decode_ret = GNUTLS_E_AGAIN;
  while ((decode_ret != GNUTLS_E_SUCCESS) &&
         (decode_ret != GNUTLS_E_INTERRUPTED)) {
    if (decode_ret == GNUTLS_E_AGAIN) {
      if (provider.remaining_bytes() == 0) {
        break;
      }
      const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
          0,
          provider.remaining_bytes());
      auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
      decode_ret = gnutls_record_recv(session, next_input.data(), next_input.size());
    } else if (decode_ret != GNUTLS_E_SUCCESS && decode_ret != GNUTLS_E_AGAIN) {
      decode_ret = gnutls_record_recv(session, nullptr, 0);
    } else {
      // Unhandled gnutls_record_recv return value.
      abort();
    }
  }

  size_t status = check_session_status(session, 1000);
  if (status != GNUTLS_E_SUCCESS) {
    fprintf(stderr, "check_session_status returned %d\n", status);
  }

  gnutls_deinit(session);

  return 0;
}