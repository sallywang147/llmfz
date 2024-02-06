#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "unicode/ustring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t srcLength = provider.ConsumeIntegralInRange<size_t>(1, 100);
  const size_t destCapacity = srcLength * 2;
  std::vector<short> src(srcLength);
  std::vector<short> dest(destCapacity);
  for (size_t i = 0; i < srcLength; ++i) {
    src[i] = provider.ConsumeIntegral<short>();
  }
  int pErrorCode = 0;
  int result = u_strToUpper_59(dest.data(), destCapacity, src.data(), srcLength,
                               nullptr, &pErrorCode);
  if (result != srcLength) {
    fprintf(stderr, "u_strToUpper_59 returned %d instead of %zd\n", result,
            srcLength);
    abort();
  }
  if (pErrorCode != 0) {
    fprintf(stderr, "u_strToUpper_59 returned error code %d\n", pErrorCode);
    abort();
  }
  return 0;
}