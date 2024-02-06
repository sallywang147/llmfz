#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create the input string
  std::string str = provider.ConsumeRemainingBytesAsString();
  struct _Str * is = Strnew_charp_n(str.c_str(), str.size());

  // Consume the character encoding scheme (CES)
  int ces = provider.ConsumeIntegral<int>();

  // Call the target function
  struct _Str * result = wc_conv_from_utf7(is, ces);

  // Clean up
  Strfree(is);
  Strfree(result);

  return 0;
}