#include <stdint.h>
#include "../src/nokogiri_gumbo.h"

extern "C" {
#include <caret_diagnostic.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 10) {
    return 0;
  }

  struct GumboInternalError error;
  struct GumboStringBuffer output;
  gumbo_string_buffer_init(&output);

  caret_diagnostic_to_string(&error, (char *)data, size, &output);
  gumbo_string_buffer_destroy(&output);

  return 0;
}