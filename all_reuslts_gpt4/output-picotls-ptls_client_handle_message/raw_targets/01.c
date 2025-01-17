#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ptls_t
  ptls_context_t ctx;
  ptls_t *tls = ptls_new(&ctx, 0);
  if (tls == nullptr) {
    return 0;
  }

  // Initialize ptls_buffer_t
  ptls_buffer_t sendbuf;
  ptls_buffer_init(&sendbuf, "", 0);

  // Initialize epoch_offsets
  size_t epoch_offsets[PTLS_MAX_EPOCHS] = { 0 };

  // Initialize in_epoch
  size_t in_epoch = stream.ConsumeIntegral<size_t>();

  // Initialize input and inlen
  std::string input = stream.ConsumeRemainingBytesAsString();
  size_t inlen = input.size();

  // Initialize properties
  ptls_handshake_properties_t properties;
  memset(&properties, 0, sizeof(properties));

  // Call the function to fuzz
  int result = ptls_client_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, (char*)input.c_str(), inlen, &properties);

  // Cleanup
  ptls_free(tls);
  ptls_buffer_dispose(&sendbuf);

  return 0;
}