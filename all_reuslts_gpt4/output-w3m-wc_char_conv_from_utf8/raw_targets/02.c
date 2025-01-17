#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a character from the data
  char c = stream.ConsumeIntegral<char>();

  // Create a wc_status struct
  struct wc_status st;
  st.state = stream.ConsumeIntegral<uint32_t>();
  st.design = stream.ConsumeIntegral<uint32_t>();
  st.ucs = stream.ConsumeIntegral<uint32_t>();
  st.utf8 = stream.ConsumeIntegral<uint32_t>();
  st.utf16 = stream.ConsumeIntegral<uint32_t>();
  st.euc = stream.ConsumeIntegral<uint32_t>();

  // Call the target function
  struct _Str *result = wc_char_conv_from_utf8(c, &st);

  // Clean up
  if (result != NULL) {
    free(result);
  }

  return 0;
}