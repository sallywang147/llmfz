#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "zopfli/blocksplitter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  const size_t blocksize = provider.ConsumeIntegral<size_t>();
  std::string in = provider.ConsumeRemainingBytesAsString();
  size_t instart = 0;
  size_t inend = in.size();

  size_t* splitpoints = nullptr;
  size_t npoints = 0;

  ZopfliBlockSplitSimple(const_cast<char*>(in.c_str()), instart, inend, blocksize, &splitpoints, &npoints);

  free(splitpoints);

  return 0;
}