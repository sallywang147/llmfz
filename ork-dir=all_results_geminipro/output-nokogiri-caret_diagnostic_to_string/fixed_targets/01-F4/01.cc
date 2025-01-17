#include "../src/nokogiri_gumbo.h"
#include <stdint.h>

extern "C" {
#include <caret_diagnostic.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 10) {
    return 0;
  }

  GumboError error;
  GumboStringBuffer output = GUMBO_STRING_BUFFER_INIT;

  error.type = GUMBO_ERR_SYNTAX;
  error.original_text = (char *)data;
  error.original_text_length = size;
  error.parser_state = NULL;

  caret_diagnostic_to_string(&error, (char *)data, size, &output);

  gumbo_string_buffer_free(&output);

  return 0;
}