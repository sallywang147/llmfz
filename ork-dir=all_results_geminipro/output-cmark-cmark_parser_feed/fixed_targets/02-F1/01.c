#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "cmark.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct cmark_parser *parser = cmark_parser_new(CMARK_OPT_DEFAULT);
  cmark_parser_feed(parser, (char *)data, size);
  cmark_node *document = cmark_parser_finish(parser);
  cmark_parser_free(parser);
  cmark_node_free(document);
  return 0;
}