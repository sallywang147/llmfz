#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ptls_context_t
  ptls_context_t ctx = {0};

  // Initialize ptls_t
  ptls_t *tls = ptls_new(&ctx, 0);
  if (tls == nullptr) {
    return 0;
  }

  // Initialize ptls_buffer_t
  ptls_buffer_t sendbuf;
  uint8_t sendbuf_small[1];
  ptls_buffer_init(&sendbuf, sendbuf_small, sizeof(sendbuf_small));

  // Initialize epoch_offsets
  size_t epoch_offsets[5] = {0, 0, 0, 0, 0};

  // Initialize in_epoch
  size_t in_epoch = stream.ConsumeIntegral<size_t>();

  // Initialize input and inlen
  std::string input = stream.ConsumeRemainingBytesAsString();
  size_t inlen = input.size();

  // Initialize ptls_handshake_properties_t
  ptls_handshake_properties_t properties = {0};

  // Call the target function
  int ret = ptls_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, (char*)input.data(), inlen, &properties);

  // Cleanup
  ptls_free(tls);
  ptls_buffer_dispose(&sendbuf);

  return 0;
}