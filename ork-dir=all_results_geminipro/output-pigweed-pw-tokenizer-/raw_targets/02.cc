#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "pw_tokenizer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pw::tokenizer::NestedMessageDetokenizer detokenizer;
  while (stream.remaining_bytes() > 0) {
    detokenizer.Process(stream.ConsumeIntegral<char>());
  }
  return 0;
}