#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wels/codec_api.h"
#include "wels/codec_app_def.h"
#include "wels/codec_def.h"
#include "wels/codec_ver.h"
#include "wels/codec_trace.h"
#include "wels/dec_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  WelsDec::CWelsDecoder decoder;
  TagParserBsInfo dstInfo;

  std::string src = stream.ConsumeRemainingBytesAsString();
  char *kpSrc = const_cast<char *>(src.c_str());
  int kiSrcLen = src.length();

  decoder.DecodeParser(&decoder, kpSrc, kiSrcLen, &dstInfo);

  return 0;
}