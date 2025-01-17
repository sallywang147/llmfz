#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "zopfli/blocksplitter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  size_t blocksize = stream.ConsumeIntegral<size_t>();
  size_t instart = stream.ConsumeIntegralInRange<size_t>(0, size);
  size_t inend = stream.ConsumeIntegralInRange<size_t>(instart, size);
  
  // ZopfliBlockSplitSimple requires a non-const char* as input
  std::vector<char> in(data, data + size);
  
  size_t* splitpoints = nullptr;
  size_t npoints = 0;

  ZopfliBlockSplitSimple(in.data(), instart, inend, blocksize, &splitpoints, &npoints);
  
  free(splitpoints);

  return 0;
}