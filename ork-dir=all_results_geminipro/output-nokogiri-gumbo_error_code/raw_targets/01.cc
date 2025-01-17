#include "../src/nokogiri_gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  GumboInternalError error;
  gumbo_init_error(&error);

  char *error_string = gumbo_error_code(&error);
  if (error_string) {
    free(error_string);
  }

  return 0;
}