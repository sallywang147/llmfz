#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wels/codec_api.h"
#include "wels/codec_def.h"
#include "wels/codec_app_def.h"
#include "wels/codec_ver.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    WelsDec::CWelsDecoder *decoder = new WelsDec::CWelsDecoder();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  // Create a WelsDec::tagSWelsDecThreadCtx object
  WelsDec::tagSWelsDecThreadCtx sThreadCtx;

  // Initialize the sThreadCtx object
  sThreadCtx.pCtx = nullptr;
  sThreadCtx.pBuf = provider.ConsumeRemainingBytes<uint8_t>().data();
  sThreadCtx.iBufLen = size;
  sThreadCtx.iThreadIdx = 0;
  sThreadCtx.iThreadNum = 1;

  // Call the target function
  decoder->ParseAccessUnit(&sThreadCtx);

  return 0;
}