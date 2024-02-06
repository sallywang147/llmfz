#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  ptls_context_t ctx = {0};
  ptls_t *tls = ptls_new(&ctx, 0);
  if (tls == NULL) {
    return 0;
  }

  ptls_buffer_t sendbuf;
  ptls_buffer_init(&sendbuf, "", 0);

  size_t epoch_offsets[5] = {0, 0, 0, 0, 0};
  size_t in_epoch = provider.ConsumeIntegralInRange<size_t>(0, 4);

  size_t inlen = provider.remaining_bytes() / 2;
  std::string input = provider.ConsumeBytesAsString(inlen);

  ptls_handshake_properties_t properties = {0};

  int ret = ptls_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, input.data(), inlen, &properties);

  ptls_free(tls);
  ptls_buffer_dispose(&sendbuf);

  return 0;
}