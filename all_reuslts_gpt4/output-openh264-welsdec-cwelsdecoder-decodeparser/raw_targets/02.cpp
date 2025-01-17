#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wels/codec_api.h"
#include "wels/codec_def.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ISVCDecoder* decoder;
  if (WelsCreateDecoder(&decoder)) {
    return 0;
  }

  SDecodingParam dec_param = {0};
  dec_param.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_DEFAULT;

  if (decoder->Initialize(&dec_param)) {
    decoder->Uninitialize();
    WelsDestroyDecoder(decoder);
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  SBufferInfo buffer_info;
  memset(&buffer_info, 0, sizeof(buffer_info));

  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<char>(next_size);

  decoder->DecodeParser(next_input.data(), next_input.size(), &buffer_info);

  decoder->Uninitialize();
  WelsDestroyDecoder(decoder);

  return 0;
}