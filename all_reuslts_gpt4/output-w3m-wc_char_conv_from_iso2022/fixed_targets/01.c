#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  char c = provider.ConsumeIntegral<char>();
  wc_status st;
  wc_char_conv_from_iso2022(c, &st);

  return 0;
}