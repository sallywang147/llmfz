#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the ptls_t structure
  ptls_context_t ctx;
  ptls_t* tls = ptls_new(&ctx, 0);
  if (tls == nullptr) {
    return 0;
  }

  // Initialize the ptls_buffer_t structure
  ptls_buffer_t sendbuf;
  ptls_buffer_init(&sendbuf, "", 0);

  // Initialize the epoch_offsets array
  size_t epoch_offsets[5] = {0, 0, 0, 0, 0};

  // Get the in_epoch value
  size_t in_epoch = stream.ConsumeIntegral<size_t>();

  // Get the input and its length
  std::string input = stream.ConsumeRemainingBytesAsString();
  size_t inlen = input.size();

  // Initialize the ptls_handshake_properties_t structure
  ptls_handshake_properties_t properties;
  memset(&properties, 0, sizeof(properties));

  // Call the target function
  int ret = ptls_client_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, const_cast<char*>(input.c_str()), inlen, &properties);

  // Cleanup
  ptls_free(tls);
  ptls_buffer_dispose(&sendbuf);

  return 0;
}