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

  char *json = pg_query_node_to_json(new_str);
  free(json);
  free(new_str);
  return 0;
}