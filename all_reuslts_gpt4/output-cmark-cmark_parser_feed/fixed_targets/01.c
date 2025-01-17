#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cmark.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  cmark_parser *parser = cmark_parser_new(CMARK_OPT_DEFAULT);
  if (!parser) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::string str = provider.ConsumeRemainingBytesAsString();
  cmark_parser_feed(parser, str.c_str(), str.size());

  cmark_node *doc = cmark_parser_finish(parser);
  cmark_parser_free(parser);
  if (doc) {
    char *rendered = cmark_render_html(doc, CMARK_OPT_DEFAULT);
    free(rendered);
    cmark_node_free(doc);
  }

  return 0;
}