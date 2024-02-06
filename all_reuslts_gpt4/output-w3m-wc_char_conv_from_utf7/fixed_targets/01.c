#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract a char
  char c = stream.ConsumeIntegral<char>();

  // Extract to user defined object
  struct wc_status st;
  size_t consumed = stream.ConsumeData(&st, sizeof(st));
  
  // Call the function
  struct _Str *result = wc_char_conv_from_utf7(c, &st);

  // Free the memory
  if (result) {
    free(result);
  }

  return 0;
}