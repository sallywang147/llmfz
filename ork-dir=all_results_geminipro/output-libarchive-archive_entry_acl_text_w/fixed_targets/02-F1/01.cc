#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "archive.h"

extern "C" {
#include <archive.h>
#include <archive_entry.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  int ret;
  struct archive *a = archive_read_new();
  struct archive_entry *entry;

  archive_read_support_filter_all(a);
  archive_read_support_format_all(a);

  Buffer buffer = {buf, len};
  archive_read_open(a, &buffer, NULL, reader_callback, NULL);

  while (1) {
    ret = archive_read_next_header(a, &entry);
    if (ret == ARCHIVE_EOF || ret == ARCHIVE_FATAL)
      break;
    if (ret == ARCHIVE_RETRY)
      continue;
    archive_entry_acl_text_w(entry, 0);
  }

  archive_read_free(a);
  return 0;
}