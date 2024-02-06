#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "pw_tokenizer/detokenizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string output_string;
  pw::tokenizer::Detokenizer detokenizer;
  size_t output_size = stream.ConsumeIntegral<size_t>();

  // Create a buffer for the output
  std::vector<char> output_buffer(output_size);

  detokenizer.DetokenizeBase64(&output_string, &detokenizer, output_buffer.data(), output_size);

  return 0;
}