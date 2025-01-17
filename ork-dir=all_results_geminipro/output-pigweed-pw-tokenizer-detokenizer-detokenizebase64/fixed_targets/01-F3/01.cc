#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "pw_tokenizer.h"

extern "C" {
#include "pw_tokenizer_detokenizer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string input_text = stream.ConsumeRemainingBytesAsString();
  pw::tokenizer::Detokenizer detokenizer;
  std::string output_text;
  detokenizer.DetokenizeBase64(&output_text, &detokenizer,
                               reinterpret_cast<char*>(const_cast<char*>(input_text.c_str())), input_text.size());
  return 0;
}