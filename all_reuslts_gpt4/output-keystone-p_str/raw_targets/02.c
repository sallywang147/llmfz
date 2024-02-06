#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "parse.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize struct parse
  struct parse p = {0};
  
  // Consume data from the stream to fill the struct parse
  p.left = stream.ConsumeIntegral<int>();
  p.right = stream.ConsumeIntegral<int>();
  p.maxlen = stream.ConsumeIntegral<int>();
  p.len = stream.ConsumeIntegral<int>();
  p.offset = stream.ConsumeIntegral<int>();
  p.error = stream.ConsumeIntegral<int>();
  p.flags = stream.ConsumeIntegral<int>();

  // Consume remaining bytes as a string and store it in the struct parse
  std::string str = stream.ConsumeRemainingBytesAsString();
  p.input = str.c_str();

  // Call the target function
  p_str(&p);

  return 0;
}