#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "unicode/utypes.h"
#include "unicode/ustring.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int destCapacity = stream.ConsumeIntegralInRange<int>(1, 1000);
  int srcLength = stream.ConsumeIntegralInRange<int>(1, 1000);
  int pErrorCode = 0;

  std::vector<UChar> src = stream.ConsumeBytes<UChar>(srcLength);
  std::vector<UChar> dest(destCapacity);

  std::string locale = stream.ConsumeRemainingBytesAsString();
  
  u_strToUpper_59(dest.data(), destCapacity, src.data(), srcLength, locale.c_str(), &pErrorCode);

  return 0;
}