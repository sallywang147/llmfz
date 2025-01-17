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
    struct _IO_FILE file;
    file._IO_read_ptr = markdown;
    file._IO_read_end = markdown + markdown_size;
    file._IO_buf_base = NULL;
    file._IO_buf_end = NULL;
    file._IO_save_base = NULL;
    file._IO_backup_base = NULL;
    file._IO_save_end = NULL;
    file._IO_marker = NULL;
    file._IO_chain = NULL;
    file._IO_wide_data = NULL;
    file._IO_flags = _IO_FILE_DONTCLOSE | _IO_FILE_NO_WRITES;
    file._IO_file_flags = _IO_FILE_DONTCLOSE | _IO_FILE_NO_WRITES;
    file._IO_eof_reached = 0;
    file._IO_error_seen = 0;
    file._IO_unlink = 0;

    cmark_parse_file(&file, fuzz_config.options);
  }
  return 0;
}