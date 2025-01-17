#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "parse.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct parse p;

  // Initialize the parse structure
  p.n = stream.ConsumeIntegral<unsigned int>();
  p.error = stream.ConsumeIntegral<unsigned int>();
  p.next = stream.ConsumeIntegral<unsigned int>();
  p.len = stream.ConsumeIntegral<unsigned int>();
  p.offset = stream.ConsumeIntegral<unsigned int>();
  p.lineno = stream.ConsumeIntegral<unsigned int>();
  p.unget = stream.ConsumeIntegral<unsigned int>();

  // Consume remaining bytes as string
  std::string str = stream.ConsumeRemainingBytesAsString();
  p.input = str.c_str();

  // Calling the function to fuzz
  p_str(&p);

  return 0;
}