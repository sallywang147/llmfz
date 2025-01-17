#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "compressor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the compressor context
  struct CompressorContext c;

  // Consume the data to select a compressor
  int compressor = stream.ConsumeIntegral<int>();

  // Start encoding with the selected compressor
  int result = compressor_start_encode(&c, compressor);

  return 0;
}