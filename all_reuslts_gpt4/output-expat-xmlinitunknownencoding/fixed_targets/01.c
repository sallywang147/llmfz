#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Define and initialize the table
  int table[256];
  for (int i = 0; i < 256; i++) {
    table[i] = stream.ConsumeIntegral<int>();
  }

  // Define and initialize the convert function
  func_type convert = NULL;

  // Define and initialize the mem and userData
  std::string mem = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string userData = stream.ConsumeRemainingBytesAsString();

  // Call the function
  struct encoding *result = XmlInitUnknownEncoding(const_cast<char*>(mem.c_str()), table, convert, const_cast<char*>(userData.c_str()));

  return 0;
}