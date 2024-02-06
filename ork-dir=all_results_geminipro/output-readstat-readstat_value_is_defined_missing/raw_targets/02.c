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
  if (!schema)
    return 0;

  readstat_variable_t *variable = schema->variables;

  while (variable) {
    size_t value = 0;
    if (variable->type == 's') {
      value = fuzzer_consume_string(parser);
    } else if (variable->type == 'n') {
      value = fuzzer_consume_number(parser);
    } else if (variable->type == 'f') {
      value = fuzzer_consume_float(parser);
    } else if (variable->type == 'd') {
      value = fuzzer_consume_double(parser);
    }

    readstat_value_is_defined_missing(value, variable->index, variable);

    variable = variable->next;
  }

  readstat_schema_free(schema);
  readstat_parser_free(parser);

  return 0;
}