#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "pw_tokenizer/public/tokenizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an instance of NestedMessageDetokenizer
  pw::tokenizer::NestedMessageDetokenizer nestedMessageDetokenizer;

  // Consume the data as characters and pass to the function
  while (stream.remaining_bytes() > 0) {
    char next_char = stream.ConsumeIntegral<char>();
    nestedMessageDetokenizer.Process(next_char);
  }

  return 0;
}