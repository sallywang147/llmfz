#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "compressor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a CompressorContext and initialize it with random data
  struct CompressorContext c;
  size_t consumed = stream.ConsumeData(&c, sizeof(c));

  // Consume an integer for the compressor parameter
  int compressor = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  compressor_start_encode(&c, compressor);

  return 0;
}