#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stddef.h>
#include <pcre2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pcre2_general_context *general_context = pcre2_general_context_create(NULL, NULL, NULL);
  if (general_context == NULL) {
    return 0;
  }

  pcre2_compile_context *compile_context = pcre2_compile_context_create(general_context);
  if (compile_context == NULL) {
    pcre2_general_context_free(general_context);
    return 0;
  }

  pcre2_compile_context_free(compile_context);
  pcre2_general_context_free(general_context);

  return 0;
}