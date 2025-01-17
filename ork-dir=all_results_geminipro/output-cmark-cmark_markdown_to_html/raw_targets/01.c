#include "cmark.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int options = CMARK_OPT_DEFAULT;

  if (size >= sizeof(options)) {
    /* The beginning of `data` is treated as fuzzer configuration */
    memcpy(&options, data, sizeof(options));

    /* Mask off valid option bits */
    options &= (CMARK_OPT_SOURCEPOS | CMARK_OPT_HARDBREAKS | CMARK_OPT_UNSAFE |
                CMARK_OPT_NOBREAKS | CMARK_OPT_NORMALIZE |
                CMARK_OPT_VALIDATE_UTF8 | CMARK_OPT_SMART);

    /* Remainder of input is the markdown */
    const char *markdown = (const char *)(data + sizeof(options));
    const size_t markdown_size = size - sizeof(options);
    char *html = cmark_markdown_to_html(markdown, markdown_size, options);
    free(html);
  }
  return 0;
}