#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "av1/decoder/decoder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize AV1Decoder
  AV1Decoder *decoder = aom_codec_av1_dx();
  if (decoder == nullptr) {
    return 0;
  }

  // Consume data for parameters
  int int_arg1 = stream.ConsumeIntegral<int>();
  int int_arg2 = stream.ConsumeIntegral<int>();

  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRandomLengthString();

  // Call the function with the fuzzed inputs
  decode_tiles_mt(decoder, const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), int_arg1, int_arg2);

  // Cleanup
  aom_codec_destroy(decoder);

  return 0;
}