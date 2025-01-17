#include <stdlib.h>
#include <time.h>

#include "../readstat.h"
#include "../test/test_buffer.h"
#include "../test/test_buffer_io.h"
#include "../test/test_types.h"

#include "fuzz_format.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  rt_buffer_t buffer = {.bytes = (char *)Data, .size = Size, .used = Size};
  rt_buffer_ctx_t buffer_ctx = {.buffer = &buffer};

  readstat_parser_t *parser = fuzzer_parser_init(Data, Size);
  readstat_set_io_ctx(parser, &buffer_ctx);

  readstat_schema_t *schema = readstat_parse_stata_dictionary(parser, NULL, NULL, NULL);
  if (!schema) {
    readstat_parser_free(parser);
    return 0;
  }

  size_t variable = 0;
  size_t value = 0;
  for (size_t i = 0; i < schema->num_variables; i++) {
    for (size_t j = 0; j < schema->variables[i].num_values; j++) {
      int missing = readstat_value_is_missing(j, i, &schema->variables[i]);
      (void)missing;
    }
  }

  readstat_schema_free(schema);
  readstat_parser_free(parser);

  return 0;
}