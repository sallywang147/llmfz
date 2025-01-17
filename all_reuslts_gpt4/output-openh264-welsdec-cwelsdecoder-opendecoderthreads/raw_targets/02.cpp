#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <memory>

#include "codec_api.h"
#include "codec_app_def.h"
#include "codec_def.h"
#include "measure_time.h"
#include "read_config.h"
#include "typedefs.h"

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize decoder
  ISVCDecoder *pDecoder;
  WelsCreateDecoder(&pDecoder);

  // Open decoder threads
  WelsDec::CWelsDecoder *decoder = static_cast<WelsDec::CWelsDecoder*>(pDecoder);
  decoder->OpenDecoderThreads(decoder);

  // Cleanup
  WelsDestroyDecoder(pDecoder);

  return 0;
}