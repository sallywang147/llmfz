#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "pw/tokenizer/detokenizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  std::string output;
  pw::tokenizer::Detokenizer detokenizer;
  detokenizer.DetokenizeBase64(&output, &detokenizer, const_cast<char*>(input.c_str()),
                               input.size());
  return 0;
}