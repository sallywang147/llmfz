#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  int ret;
  struct archive_entry *entry;
  entry = archive_entry_new();
  archive_entry_set_pathname(entry, "some/path");

  char *acl_text;
  size_t acl_len;
  struct archive_string_conv *sc;
  sc = archive_string_conversion_from_charset("UTF-8", "UTF-8", 0);

  ret = _archive_entry_acl_text_l(entry, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
                                &acl_text, &acl_len, sc);
  if (ret != ARCHIVE_OK)
    return 0;
  free(acl_text);

  archive_entry_free(entry);
  archive_string_conversion_free(sc);
  return 0;
}