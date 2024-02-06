#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ptls_context_t
  ptls_context_t ctx;
  memset(&ctx, 0, sizeof(ctx));

  // Initialize ptls_t
  ptls_t *tls = ptls_new(&ctx, 0);
  if (tls == nullptr) {
    return 0;
  }

  // Initialize ptls_buffer_t
  ptls_buffer_t sendbuf;
  ptls_buffer_init(&sendbuf, "", 0);

  // Initialize epoch_offsets
  size_t epoch_offsets[5] = {0};

  // Consume data for in_epoch
  size_t in_epoch = stream.ConsumeIntegral<size_t>();

  // Consume data for input and inlen
  size_t inlen = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::string input = stream.ConsumeBytesAsString(inlen);

  // Initialize ptls_handshake_properties_t
  ptls_handshake_properties_t properties;
  memset(&properties, 0, sizeof(properties));

  // Call the target function
  int ret = ptls_server_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, const_cast<char*>(input.c_str()), inlen, &properties);

  // Cleanup
  ptls_free(tls);
  ptls_buffer_dispose(&sendbuf);

  return 0;
}