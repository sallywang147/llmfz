#include "ucl.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/tree.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We dont null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }
  char *data_copy = (char *)malloc(size + 1);
  memcpy(data_copy, data, size);
  data_copy[size] = '\0';

  struct ucl_parser *parser;
  parser = ucl_parser_new(0);

  if (ucl_parser_insert_chunk(parser, data_copy, size + 1)) {
    free(data_copy);
    return 0;
  }

  if (ucl_parser_get_error(parser) != NULL) {
    free(data_copy);
    return 0;
  }

  ucl_parser_free(parser);
  free(data_copy);
  return 0;
}