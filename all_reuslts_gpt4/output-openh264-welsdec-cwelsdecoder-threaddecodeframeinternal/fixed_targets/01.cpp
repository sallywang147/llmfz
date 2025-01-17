#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "codec_api.h"
#include "codec_app_def.h"
#include "codec_def.h"
#include "codec_ver.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    WelsDec::CWelsDecoder decoder;
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  // Extracting inputs for ThreadDecodeFrameInternal function
  std::string kpSrc = provider.ConsumeBytesAsString(provider.remaining_bytes() / 2);
  int kiSrcLen = kpSrc.size();
  char* ppDst;
  WelsDec::TagBufferInfo pDstInfo;

  // Calling the function to fuzz
  decoder.ThreadDecodeFrameInternal(&decoder, kpSrc.data(), kiSrcLen, &ppDst, &pDstInfo);

  return 0;
}