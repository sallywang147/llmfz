#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "lz4hc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input_string = stream.ConsumeRemainingBytesAsString();
  char* input_data = const_cast<char*>(input_string.c_str());
  const size_t input_size = input_string.size();

  const size_t max_output_size = stream.ConsumeIntegralInRange<size_t>(
      0, input_size * 2);
  char* output_data = new char[max_output_size];
  const int compression_level = stream.ConsumeIntegralInRange<int>(0, 20);

  const int result = LZ4_compressHC2_limitedOutput(
      input_data, output_data, input_size, max_output_size, compression_level);

  delete[] output_data;

  return 0;
}