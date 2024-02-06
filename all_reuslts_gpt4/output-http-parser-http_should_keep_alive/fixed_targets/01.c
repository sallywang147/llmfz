#include "http_parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  http_parser parser;
  http_parser_init(&parser, HTTP_BOTH);
  http_parser_execute(&parser, NULL, (char *)data, size);
  http_should_keep_alive(&parser);
  return 0;
}