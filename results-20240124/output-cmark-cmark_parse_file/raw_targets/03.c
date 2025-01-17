 #include "cmark.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size >= sizeof(int)) {
    /* The beginning of `data` is treated as fuzzer configuration */
    int options = *(int *)data;

    /* Mask off valid option bits */
    options &= (CMARK_OPT_SOURCEPOS | CMARK_OPT_HARDBREAKS | CMARK_OPT_UNSAFE | CMARK_OPT_NOBREAKS | CMARK_OPT_NORMALIZE | CMARK_OPT_VALIDATE_UTF8 | CMARK_OPT_SMART);

    /* Remainder of input is the markdown */
    const char *markdown = (const char *)(data + sizeof(int));
    const size_t markdown_size = size - sizeof(int);
    struct _IO_FILE stream;
    stream.data = (void *)markdown;
    stream._IO_read_ptr = (void *)markdown;
    stream._IO_read_end = (void *)(markdown + markdown_size);
    stream._IO_write_ptr = (void *)markdown;
    stream._IO_write_end = (void *)(markdown + markdown_size);
    cmark_parse_file(&stream, options);
  }
  return 0;
}