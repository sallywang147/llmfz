#include <utf8proc.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Call the function
  char *version = utf8proc_unicode_version();

  return 0;
}