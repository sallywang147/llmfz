#include "../src/nokogiri_gumbo.h"
#include <stdint.h>

extern "C" {
#include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 10) {
    return 0;
  }

  GumboInternalError error;
  error.type = GUMBO_ERR_SYNTAX;
  error.original_text = (char *)data;
  error.original_text_length = size;
  error.position = size / 2;
  error.context = NULL;
  error.context_length = 0;

  char *output = NULL;
  size_t output_length = gumbo_caret_diagnostic_to_string(&error, (char *)data, size, &output);
  if (output_length == 0) {
    return 0;
  }

  free(output);

  return 0;
}