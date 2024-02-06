#include <stdint.h>
#include <nokogiri_gumbo.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 10) {
    return 0;
  }

  GumboInternalError error;
  error.line = 0;
  error.column = 0;
  error.message = "test";
  error.code = GUMBO_ERR_OK;
  error.parser_state = nullptr;

  char *output;
  size_t output_length = gumbo_caret_diagnostic_to_string(&error, (char *)data, size, &output);

  if (output_length > 0) {
    free(output);
  }

  return 0;
}