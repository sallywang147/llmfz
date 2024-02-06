#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pcre2_real_general_context_8* gcontext =
      pcre2_real_general_context_create_8(NULL, NULL);
  if (gcontext == NULL) {
    return 0;
  }

  struct pcre2_real_convert_context_8* ccontext =
      pcre2_convert_context_create_8(gcontext);
  if (ccontext == NULL) {
    pcre2_real_general_context_free_8(gcontext);
    return 0;
  }

  const char* input = stream.ConsumeRemainingBytesAsString().c_str();
  size_t input_length = strlen(input);
  const char* output = pcre2_convert_simple_8(ccontext, input, input_length,
                                              PCRE2_CONVERT_NO_SUBSTITUTE);
  if (output == NULL) {
    pcre2_convert_context_free_8(ccontext);
    pcre2_real_general_context_free_8(gcontext);
    return 0;
  }

  pcre2_convert_context_free_8(ccontext);
  pcre2_real_general_context_free_8(gcontext);
  return 0;
}