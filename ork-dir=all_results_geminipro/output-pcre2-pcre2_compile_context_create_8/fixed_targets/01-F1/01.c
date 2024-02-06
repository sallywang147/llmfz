#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "pcre2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pcre2_general_context_8 *gcontext = pcre2_general_context_create_8(NULL);
  if (gcontext == NULL) {
    return 0;
  }
  pcre2_compile_context_8 *context = pcre2_compile_context_create_8(gcontext);
  if (context == NULL) {
    pcre2_general_context_free_8(gcontext);
    return 0;
  }
  pcre2_compile_context_free_8(context);
  pcre2_general_context_free_8(gcontext);
  return 0;
}