#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wels/codec_api.h"
#include "wels/codec_app_def.h"
#include "wels/codec_def.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the decoder
  ISVCDecoder* decoder = nullptr;
  int rv = WelsCreateDecoder(&decoder);
  if (rv != 0 || decoder == nullptr) {
    return 0;  // Cannot test if we can't create a decoder.
  }

  // Set decoder parameters
  SDecodingParam dec_param = {0};
  dec_param.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_DEFAULT;
  decoder->Initialize(&dec_param);

  // Prepare the data provider
  FuzzedDataProvider provider(data, size);

  // Prepare the output buffer
  char* output_buffer = nullptr;
  SBufferInfo buffer_info;
  memset(&buffer_info, 0, sizeof(SBufferInfo));

  // Consume data and call the function to fuzz
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0, provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<char>(next_size);

    decoder->ThreadDecodeFrameInternal(next_input.data(), next_input.size(),
                                       &output_buffer, &buffer_info);
  }

  // Cleanup
  decoder->Uninitialize();
  WelsDestroyDecoder(decoder);

  return 0;
}