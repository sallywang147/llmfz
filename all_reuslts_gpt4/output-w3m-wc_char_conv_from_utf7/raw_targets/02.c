#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "wc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract char value
  char c = stream.ConsumeIntegral<char>();

  // Extract to user defined object
  struct wc_status st;
  size_t consumed = stream.ConsumeData(&st, sizeof(st));

  // Call the target function
  struct _Str *result = wc_char_conv_from_utf7(c, &st);

  return 0;
}