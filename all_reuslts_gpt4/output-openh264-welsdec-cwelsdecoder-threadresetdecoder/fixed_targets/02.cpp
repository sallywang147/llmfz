#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "codec_def.h"
#include "codec_api.h"
#include "codec_app_def.h"
#include "wels_common_defs.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  WelsDec::CWelsDecoder decoder;
  WelsDec::TagWelsDecoderContext* pCtx = nullptr;

  decoder.ThreadResetDecoder(&pCtx);

  return 0;
}