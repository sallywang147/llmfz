#include <fuzzer/FuzzedDataProvider.h>
#include <gnutls/gnutls.h>
#include <cstdint>
#include <cstddef>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize a gnutls session
  gnutls_session_t session;
  gnutls_init(&session, GNUTLS_SERVER);

  // Generate data and seq
  size_t data_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> data_buffer = stream.ConsumeBytes<char>(data_size);
  std::vector<char> seq = stream.ConsumeRemainingBytes<char>();

  // Call the function to fuzz
  gnutls_record_recv_seq(session, data_buffer.data(), data_size, seq.data());

  // Cleanup
  gnutls_deinit(session);

  return 0;
}