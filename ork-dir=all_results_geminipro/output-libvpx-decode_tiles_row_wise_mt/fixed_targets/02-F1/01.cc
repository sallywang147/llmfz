#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vpx/vpx_decoder.h"
#include "vpx/vp8dx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    vpx_codec_dec_init(&vpx_codec_vp9_dx, vpx_codec_vp9_dx(), NULL, 0);
    initialized = true;
  }
  int ret;
  vpx_codec_ctx_t codec;
  vpx_codec_dec_cfg_t cfg = {0, 0, 0};
  if (vpx_codec_dec_init(&codec, &vpx_codec_vp9_dx, &cfg, 0)) {
    return 0;
  }

  std::vector<uint8_t> output_buffer(4096);

  size_t output_written = 0;
  // Initially, start by feeding the decoder more data.
  int decode_ret = VPX_CODEC_OK;
  FuzzedDataProvider provider(data, size);
  while ((decode_ret != VPX_CODEC_ERROR)) {
    if (decode_ret == VPX_CODEC_OK) {
      if (provider.remaining_bytes() == 0) {
        break;
      }
      const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
          0,
          provider.remaining_bytes());
      auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
      decode_ret = vpx_codec_decode(&codec, next_input.data(), next_input.size(),
                                 output_buffer.data(), output_buffer.size(),
                                 &output_written);
    } else if (decode_ret != VPX_CODEC_ERROR && decode_ret != VPX_CODEC_OK) {
      decode_ret = vpx_codec_decode(&codec, nullptr, 0, output_buffer.data(),
                                 output_buffer.size(), &output_written);
    } else {
      // Unhandled vpx_codec_decode return value.
      abort();
    }
  }
  char *decoded_data = decode_tiles_row_wise_mt(&codec, nullptr, nullptr);
  free(decoded_data);
  vpx_codec_destroy(&codec);

  return 0;
}