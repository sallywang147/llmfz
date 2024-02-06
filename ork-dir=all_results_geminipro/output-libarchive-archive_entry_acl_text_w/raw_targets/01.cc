#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  struct archive_entry *entry = archive_entry_new();
  archive_entry_set_pathname(entry, reinterpret_cast<const char *>(buf), len);
  archive_entry_acl_text_w(entry, 0);
  archive_entry_free(entry);

  return 0;
}