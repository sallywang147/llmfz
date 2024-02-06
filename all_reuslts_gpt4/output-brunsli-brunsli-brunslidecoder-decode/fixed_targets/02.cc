#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "brunsli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the decoder
  brunsli::BrunsliDecoder decoder;

  // Consume data for input buffer
  size_t input_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> input_buffer(input_size);
  size_t consumed = stream.ConsumeData(input_buffer.data(), input_size);

  // Consume data for output buffer
  size_t output_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> output_buffer(output_size);

  // Call the function to fuzz
  decoder.Decode(&input_size, &input_buffer[0], &output_size, &output_buffer[0]);

  return 0;
}