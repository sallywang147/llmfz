#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "compressor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize CompressorContext
  struct CompressorContext *c = compressor_init();
  if (!c) {
    return 0;
  }

  // Consume a boolean value for 'finalize' parameter
  bool finalize = stream.ConsumeBool();

  // Consume some bytes for 'p' parameter
  std::string p = stream.ConsumeRemainingBytesAsString();
  
  // Initialize 'sz' parameter as the size of 'p'
  size_t sz = p.size();

  // Initialize 'ret_done' parameter
  size_t ret_done = 0;
  
  // Call the function
  compressor_encode(c, finalize, p.data(), sz, &ret_done);
  
  // Clean up
  compressor_free(c);

  return 0;
}