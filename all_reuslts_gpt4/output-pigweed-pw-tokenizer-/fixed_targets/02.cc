#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pw_tokenizer/public/tokenizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the NestedMessageDetokenizer
  pw::tokenizer::NestedMessageDetokenizer nested_message_detokenizer;

  // Consume the data to feed to the function
  while (stream.remaining_bytes() > 0) {
    char next_char = stream.ConsumeIntegral<char>();
    nested_message_detokenizer.Process(next_char);
  }

  return 0;
}