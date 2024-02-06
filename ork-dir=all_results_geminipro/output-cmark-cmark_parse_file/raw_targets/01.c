#include "cmark.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct __attribute__((packed)) {
    int options;
  } fuzz_config;

  if (size >= sizeof(fuzz_config)) {
    /* The beginning of `data` is treated as fuzzer configuration */
    memcpy(&fuzz_config, data, sizeof(fuzz_config));

    /* Mask off valid option bits */
    fuzz_config.options &= (CMARK_OPT_SOURCEPOS | CMARK_OPT_HARDBREAKS | CMARK_OPT_UNSAFE | CMARK_OPT_NOBREAKS | CMARK_OPT_NORMALIZE | CMARK_OPT_VALIDATE_UTF8 | CMARK_OPT_SMART);

    /* Remainder of input is the markdown */
    const char *markdown = (const char *)(data + sizeof(fuzz_config));
    const size_t markdown_size = size - sizeof(fuzz_config);

    FILE *f = fmemopen((void *)markdown, markdown_size, "r");
    cmark_node *doc = cmark_parse_file(f, fuzz_config.options);

    free(cmark_render_commonmark(doc, fuzz_config.options, 0));
    free(cmark_render_html(doc, fuzz_config.options));
    free(cmark_render_latex(doc, fuzz_config.options, 0));
    free(cmark_render_man(doc, fuzz_config.options, 0));
    free(cmark_render_xml(doc, fuzz_config.options));

    cmark_node_free(doc);
    fclose(f);
  }
  return 0;
}