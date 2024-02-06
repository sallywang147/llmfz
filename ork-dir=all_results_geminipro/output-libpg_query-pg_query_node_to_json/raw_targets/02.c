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

  PgQueryNode *node = pg_query_parse(new_str);
  if (node == NULL) {
    free(new_str);
    return 0;
  }

  char *json = pg_query_node_to_json(node);
  if (json == NULL) {
    pg_query_free_parse_result(node);
    free(new_str);
    return 0;
  }

  free(json);
  pg_query_free_parse_result(node);
  free(new_str);
  return 0;
}