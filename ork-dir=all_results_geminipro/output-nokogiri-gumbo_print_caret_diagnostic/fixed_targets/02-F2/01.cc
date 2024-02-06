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
  error.line_number = 0;
  error.column_number = 0;

  gumbo_print_caret_diagnostic(&error, (char *)data, size);

  return 0;
}