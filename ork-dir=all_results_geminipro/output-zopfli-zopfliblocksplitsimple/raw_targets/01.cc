#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "deflate.h"
#include "zopfli.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string input = stream.ConsumeRemainingBytesAsString();
  const size_t instart = stream.ConsumeIntegralInRange<size_t>(0, input.size());
  const size_t inend = stream.ConsumeIntegralInRange<size_t>(instart, input.size());
  const size_t blocksize = stream.ConsumeIntegralInRange<size_t>(1, input.size());

  size_t *splitpoints = nullptr;
  size_t npoints = 0;
  ZopfliBlockSplitSimple(const_cast<char*>(input.data()), instart, inend, blocksize,
                         &splitpoints, &npoints);

  if (splitpoints != nullptr) {
    free(splitpoints);
  }

  return 0;
}