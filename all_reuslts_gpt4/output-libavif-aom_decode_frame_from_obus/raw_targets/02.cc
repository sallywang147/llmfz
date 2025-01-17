#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aom/aom_decoder.h"
#include "aom/aomdx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  aom_codec_ctx_t codec;
  if (aom_codec_dec_init(&codec, aom_codec_av1_dx(), NULL, 0)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string obu = stream.ConsumeRandomLengthString();
  std::string obu_end = stream.ConsumeRandomLengthString();
  char* obu_ptr = obu.c_str();
  char* obu_end_ptr = obu_end.c_str();
  char* pbi = nullptr;

  aom_decode_frame_from_obus(&codec, obu_ptr, obu_end_ptr, &pbi);

  aom_codec_destroy(&codec);
  return 0;
}