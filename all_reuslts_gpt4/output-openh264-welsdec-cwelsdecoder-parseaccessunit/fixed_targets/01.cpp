#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "wels/codec_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Create a FuzzedDataProvider instance.
  FuzzedDataProvider stream(data, size);
  
  // Create a new decoder instance.
  ISVCDecoder* decoder = nullptr;
  WelsCreateDecoder(&decoder);
  
  // Initialize the decoder.
  SDecodingParam dec_param = {0};
  dec_param.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_DEFAULT;
  decoder->Initialize(&dec_param);
  
  // Create a new thread context.
  WelsDec::tagSWelsDecThreadCtx sThreadCtx;
  
  // Parse the input data.
  decoder->ParseAccessUnit(&sThreadCtx, data, size);
  
  // Uninitialize the decoder.
  decoder->Uninitialize();
  
  // Delete the decoder instance.
  WelsDestroyDecoder(decoder);
  
  return 0;
}