#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  char c = provider.ConsumeIntegral<char>();
  struct wc_status st;
  st.ss = provider.ConsumeIntegral<uint8_t>();
  st.design = provider.ConsumeIntegral<uint8_t>();
  st.gl = provider.ConsumeIntegral<uint8_t>();
  st.gr = provider.ConsumeIntegral<uint8_t>();
  st.is_iso2022 = provider.ConsumeIntegral<uint8_t>();
  st.esc = provider.ConsumeIntegral<uint8_t>();
  st.cr = provider.ConsumeIntegral<uint8_t>();

  struct _Str *result = wc_char_conv_from_iso2022(c, &st);

  return 0;
}