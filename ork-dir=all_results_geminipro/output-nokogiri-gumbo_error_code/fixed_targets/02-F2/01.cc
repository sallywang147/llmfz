#include "../src/nokogiri_gumbo.h"
#include <stdint.h>

extern "C" {
#include <gumbo.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  GumboInternalError error;
  gumbo_init_error(&error);
  char *result = gumbo_error_string(&error);  // Fix: gumbo_error_code to gumbo_error_string
  if (result) {
    free(result);
  }
  return 0;
}