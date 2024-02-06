#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cmark.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct cmark_strbuf buf = CMARK_BUF_INIT;
  struct __attribute__((packed)) {
    int options;
    int width;
  } fuzz_config;

  if (size >= sizeof(fuzz_config)) {
    /* The beginning of `data` is treated as fuzzer configuration */
    memcpy(&fuzz_config, data, sizeof(fuzz_config));

    /* Mask off valid option bits */
    fuzz_config.options &= (CMARK_OPT_SOURCEPOS | CMARK_OPT_HARDBREAKS | CMARK_OPT_UNSAFE | CMARK_OPT_NOBREAKS | CMARK_OPT_NORMALIZE | CMARK_OPT_VALIDATE_UTF8 | CMARK_OPT_SMART);

    /* Remainder of input is the markdown */
    const char *markdown = (const char *)(data + sizeof(fuzz_config));
    const size_t markdown_size = size - sizeof(fuzz_config);
    cmark_node *doc = cmark_parse_document(markdown, markdown_size, fuzz_config.options);

    houdini_escape_html(&buf, cmark_render_commonmark(doc, fuzz_config.options, fuzz_config.width), strlen(cmark_render_commonmark(doc, fuzz_config.options, fuzz_config.width)));
    free(cmark_render_commonmark(doc, fuzz_config.options, fuzz_config.width));
    cmark_node_free(doc);
  }
  cmark_strbuf_free(&buf);
  return 0;
}