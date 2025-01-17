#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/msgfmt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  UErrorCode status = U_ZERO_ERROR;
  icu_75::MessageFormat msgFormat("", "en_US", status);
  if (U_FAILURE(status)) {
    return 0;
  }

  msgFormat.cacheExplicitFormats(&status);

  return 0;
}