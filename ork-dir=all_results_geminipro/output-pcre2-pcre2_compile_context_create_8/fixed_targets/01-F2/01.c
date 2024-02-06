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
  const char *error;
  int erroffset;
  pcre2_code_8 *re = pcre2_compile_8(
      (PCRE2_SPTR8)stream.ConsumeRemainingBytes(), PCRE2_ZERO_TERMINATED, 0, &error, &erroffset, context);
  pcre2_compile_context_free_8(context);
  pcre2_general_context_free_8(gcontext);
  pcre2_code_free_8(re);
  return 0;
}