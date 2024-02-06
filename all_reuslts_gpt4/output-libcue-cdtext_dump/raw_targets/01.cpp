#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cdtext.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Define and initialize the parameters for cdtext_dump
  struct Cdtext cdtext;
  int arg = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  cdtext_dump(&cdtext, arg);

  return 0;
}