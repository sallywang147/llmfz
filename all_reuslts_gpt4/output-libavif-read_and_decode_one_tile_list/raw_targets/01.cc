#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  aom_codec_ctx_t codec;
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), NULL, 0)) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t buffer1_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes()/2);
  auto buffer1 = provider.ConsumeBytes<char>(buffer1_size);
  const size_t buffer2_size = provider.remaining_bytes();
  auto buffer2 = provider.ConsumeBytes<char>(buffer2_size);

  struct aom_read_bit_buffer rb = { buffer1.data(), buffer1.data() + buffer1.size(), 0, 0, {0} };
  char *buffer3 = nullptr;
  int buffer3_size = 0;

  read_and_decode_one_tile_list((struct AV1Decoder *)codec.dec, &rb, buffer2.data(), buffer2.data() + buffer2.size(), &buffer3, &buffer3_size);

  aom_codec_destroy(&codec);
  return 0;
}