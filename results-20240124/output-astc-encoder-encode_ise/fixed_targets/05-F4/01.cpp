#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "astc_codec_internals.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int quant_level = stream.ConsumeIntegral<int>();
  int character_count = stream.ConsumeIntegral<int>();
  char* input_data = const_cast<char*>(stream.ConsumeRemainingBytes<char>().data());
  char* output_data = const_cast<char*>(stream.ConsumeRemainingBytes<char>().data());
  int bit_offset = stream.ConsumeIntegral<int>();

  encode_ise(quant_level, character_count, input_data, output_data, bit_offset);

  return 0;
}