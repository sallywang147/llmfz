#include <pg_query.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <libpq-fe.h>
}

void pg_query_nodes_to_protobuf(char *);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  PGresult *res = PQexec(new_str);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    PQclear(res);
    free(new_str);
    return 0;
  }

  int num_rows = PQntuples(res);
  for (int i = 0; i < num_rows; i++) {
    int num_cols = PQnfields(res);
    for (int j = 0; j < num_cols; j++) {
      char *value = PQgetvalue(res, i, j);
      if (value != NULL) {
        printf("%s", value);
      }
    }
    printf("\n");
  }

  pg_query_nodes_to_protobuf(new_str);

  PQclear(res);
  free(new_str);
  return 0;
}