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

/*
 * To build locally:
 * CC=clang CXX=clang++ CFLAGS="-fsanitize=address,fuzzer-no-link -g" CXXFLAGS="-fsanitize=address,fuzzer-no-link -g" LDFLAGS="-fsanitize=address,fuzzer-no-link" make -j$(nproc) USE_ASM=No BUILDTYPE=Debug libraries
 * clang++ -o decoder_fuzzer -fsanitize=address -g -O1 -I./codec/api/wels -I./codec/console/common/inc -I./codec/common/inc -L. -lFuzzer -lstdc++ decoder_fuzzer.cpp libopenh264.a
 */

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a decoder instance
  ISVCDecoder *pDecoder;
  WelsCreateDecoder(&pDecoder);

  // Initialize the decoder
  SDecodingParam sDecParam = {0};
  sDecParam.eEcActiveIdc = ERROR_CON_SLICE_COPY;
  sDecParam.sVideoProperty.eVideoBsType = VIDEO_BITSTREAM_AVC;
  pDecoder->Initialize(&sDecParam);

  // Cast the decoder to CWelsDecoder to access the OpenDecoderThreads method
  WelsDec::CWelsDecoder* cwelsDecoder = static_cast<WelsDec::CWelsDecoder*>(pDecoder);

  // Call the method to fuzz
  cwelsDecoder->OpenDecoderThreads(cwelsDecoder);

  // Clean up
  pDecoder->Uninitialize();
  WelsDestroyDecoder(pDecoder);

  return 0;
}