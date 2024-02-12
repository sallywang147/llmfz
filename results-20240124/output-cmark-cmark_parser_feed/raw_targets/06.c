 #include "cmark.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct cmark_parser *parser = cmark_parser_new(CMARK_OPT_SOURCEPOS | CMARK_OPT_HARDBREAKS | CMARK_OPT_UNSAFE | CMARK_OPT_NOBREAKS | CMARK_OPT_NORMALIZE | CMARK_OPT_VALIDATE_UTF8 | CMARK_OPT_SMART);
  if (parser == NULL) {
    return 0;
  }

  cmark_parser_feed(parser, (char *)data, size);
  cmark_parser_finish(parser);
  cmark_parser_free(parser);

  return 0;
}