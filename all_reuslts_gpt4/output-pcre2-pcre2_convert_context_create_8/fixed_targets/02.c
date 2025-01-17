#include <fuzzer/FuzzedDataProvider.h>
#include <pcre2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a general context.
  pcre2_general_context_8 *gcontext = pcre2_general_context_create_8(NULL, NULL, NULL);
  if (!gcontext) {
    return 0;
  }

  // Call the target function
  pcre2_convert_context_8 *ccontext = pcre2_convert_context_create_8(gcontext);

  // Clean up
  pcre2_general_context_free_8(gcontext);
  if (ccontext) {
    pcre2_convert_context_free_8(ccontext);
  }

  return 0;
}