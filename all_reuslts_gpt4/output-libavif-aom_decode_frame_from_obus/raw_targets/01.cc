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
  aom_codec_dec_cfg_t cfg = {0, 0, 0, CONFIG_LOWBITDEPTH};
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), &cfg, 0))
    return 0;

  FuzzedDataProvider provider(data, size);

  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<char>(next_size);

  const size_t next_size2 = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input2 = provider.ConsumeBytes<char>(next_size2);

  const size_t next_size3 = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input3 = provider.ConsumeBytes<char>(next_size3);

  char* next_input3_ptr = next_input3.data();

  aom_decode_frame_from_obus(&codec, next_input.data(), next_input2.data(), &next_input3_ptr);

  aom_codec_destroy(&codec);
  
  return 0;
}