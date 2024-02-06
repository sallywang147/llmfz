#include <pg_query.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  PgQueryProtobufParseResult result = pg_query_parse_protobuf(new_str);
  pg_query_parse_protobuf_opts(&result, new_str, size);

  free(new_str);
  return 0;
}