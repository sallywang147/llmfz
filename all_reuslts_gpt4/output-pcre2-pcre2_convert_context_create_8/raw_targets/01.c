#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize general context
  pcre2_general_context_8 *gcontext = pcre2_general_context_create_8(NULL, NULL, NULL);
  if (gcontext == NULL) {
    return 0;
  }

  // Create convert context
  pcre2_convert_context_8 *ccontext = pcre2_convert_context_create_8(gcontext);
  if (ccontext == NULL) {
    pcre2_general_context_free_8(gcontext);
    return 0;
  }

  // Free the contexts
  pcre2_convert_context_free_8(ccontext);
  pcre2_general_context_free_8(gcontext);

  return 0;
}