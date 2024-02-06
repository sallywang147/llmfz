#include <stdlib.h>
#include <time.h>

#include "../readstat.h"
#include "../test/test_buffer.h"
#include "../test/test_buffer_io.h"
#include "../test/test_types.h"

#include "fuzz_format.h"

extern "C" {
#include "../src/readstat_parser.h"
#include "../src/readstat_schema.h"
#include "../src/readstat_value.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  rt_buffer_t buffer = {.bytes = (char *)Data, .size = Size, .used = Size};
  rt_buffer_ctx_t buffer_ctx = {.buffer = &buffer};

  readstat_parser_t *parser = fuzzer_parser_init(Data, Size);
  readstat_set_io_ctx(parser, &buffer_ctx);

  readstat_schema_t *schema = readstat_parse_stata_dictionary(parser, NULL, NULL, NULL);
  if (schema) {
    readstat_variable_t *variable = schema->variables;
    for (; variable; variable = variable->next) {
      for (size_t value = 0; value < variable->value_count; value++) {
        readstat_value_is_defined_missing(value, variable->index, variable);
      }
    }
    readstat_schema_free(schema);
  }
  readstat_parser_free(parser);

  return 0;
}