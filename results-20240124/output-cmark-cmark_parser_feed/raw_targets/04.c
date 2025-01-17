 #include "cmark.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct cmark_parser *parser = cmark_parser_new(CMARK_OPT_DEFAULT);
  if (parser == NULL) {
    return 0;
  }

  cmark_parser_feed(parser, (char *)data, size);
  cmark_node *doc = cmark_parser_finish(parser);
  cmark_parser_free(parser);

  free(cmark_render_commonmark(doc, CMARK_OPT_DEFAULT, 0));
  free(cmark_render_html(doc, CMARK_OPT_DEFAULT));
  free(cmark_render_latex(doc, CMARK_OPT_DEFAULT, 0));
  free(cmark_render_man(doc, CMARK_OPT_DEFAULT, 0));
  free(cmark_render_xml(doc, CMARK_OPT_DEFAULT));

  cmark_node_free(doc);

  return 0;
}