#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cmark-gfm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  cmark_gfm_core_extensions_ensure_registered();
  cmark_parser *parser = cmark_parser_new(CMARK_OPT_DEFAULT);

  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRemainingBytesAsString();
  cmark_parser_feed(parser, input.c_str(), input.size());

  cmark_node *doc = cmark_parser_finish(parser);
  cmark_parser_free(parser);

  char *rendered = cmark_render_html(doc, CMARK_OPT_DEFAULT, NULL);
  free(rendered);
  cmark_node_free(doc);

  return 0;
}