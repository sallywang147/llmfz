#include "../src/nokogiri_gumbo.h"
#include <stdint.h>

extern "C" {
#include <gumbo.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 10) {
    return 0;
  }

  GumboInternalError error;
  gumbo_init_error(&error);

  gumbo_print_caret_diagnostic(&error, (char *)data, size);

  gumbo_free_error(&error);

  return 0;
}