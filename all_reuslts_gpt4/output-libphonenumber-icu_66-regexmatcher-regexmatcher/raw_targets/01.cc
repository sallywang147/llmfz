#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unicode/regex.h"
#include "unicode/utext.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Consume data for flags and status
  int flags = provider.ConsumeIntegral<int>();
  int status = 0;

  // Consume data for regexp
  std::string regexp_str = provider.ConsumeRemainingBytesAsString();
  UText* regexp = utext_openUTF8(nullptr, regexp_str.c_str(), regexp_str.size(), &status);
  if (status != U_ZERO_ERROR) {
    utext_close(regexp);
    return 0;
  }

  // Call the target function
  icu_66::RegexMatcher matcher(regexp, flags, &status);
  if (status != U_ZERO_ERROR) {
    utext_close(regexp);
    return 0;
  }

  // Cleanup
  utext_close(regexp);

  return 0;
}