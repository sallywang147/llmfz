#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    aom_codec_dec_init(&aom_codec_av1_dec, NULL, 0, 0);
    initialized = true;
  }
  AV1Decoder* handle = aom_codec_av1_dec_alloc(NULL, 0);
  if (handle == nullptr) {
    return 0;
  }

  std::vector<uint8_t> output_buffer(aom_codec_dec_get_frame_buffer(
      &aom_codec_av1_dec, handle, NULL));

  size_t output_written = 0;
  // Initially, start by feeding the decoder more data.
  int decode_ret = AOM_CODEC_OK;
  FuzzedDataProvider provider(data, size);
  while ((decode_ret != AOM_CODEC_ERROR)) {
    if (decode_ret == AOM_CODEC_OK) {
      if (provider.remaining_bytes() == 0
          || aom_codec_decode_frame(
                 &aom_codec_av1_dec, handle, provider.ConsumeRemainingBytes(),
                 provider.remaining_bytes(), nullptr) != AOM_CODEC_OK) {
        break;
      }
      decode_ret = aom_codec_decode_frame_to_buffer(
          &aom_codec_av1_dec, handle, output_buffer.data(),
          output_buffer.size(), nullptr);
    } else if (decode_ret != AOM_CODEC_ERROR) {
      decode_ret = aom_codec_decode_frame_to_buffer(
          &aom_codec_av1_dec, handle, output_buffer.data(),
          output_buffer.size(), nullptr);
    } else {
      // Unhandled aom_codec_decode_frame_to_buffer return value.
      abort();
    }
  }

  // Call the function that was not called in the original code.
  aom_decode_frame_from_obus(handle, NULL, NULL, NULL);

  aom_codec_av1_dec_free(&handle);

  return 0;
}