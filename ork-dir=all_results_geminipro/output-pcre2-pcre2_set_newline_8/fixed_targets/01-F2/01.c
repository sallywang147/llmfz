#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "pcre2.h"

#include <pcre2posix.h>

extern "C" {
#include <pcre2posix.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pcre2_real_compile_context_8* ccontext =
      pcre2_compile_context_create_8(nullptr);
  if (ccontext == nullptr) {
    return 0;
  }
  const int newline = stream.ConsumeIntegral<int>();
  const int result = pcre2_set_newline_8(ccontext, newline);
  if (result != 0) {
    return 0;
  }
  pcre2_compile_context_free_8(ccontext);
  return 0;
}