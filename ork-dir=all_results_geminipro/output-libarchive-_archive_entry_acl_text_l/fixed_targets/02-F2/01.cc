#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "archive.h"

extern "C" {
#include <libarchive/archive_entry.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int ret;
  struct archive_entry *entry = archive_entry_new();

  std::vector<uint8_t> acl_text(size);
  size_t len = acl_text.size();
  ret = archive_entry_acl_text_l(entry, ARCHIVE_ENTRY_ACL_TYPE_ACCESS,
                                 reinterpret_cast<char *>(acl_text.data()), &len,
                                 nullptr);
  if (ret != ARCHIVE_OK)
    return 0;

  archive_entry_free(entry);
  return 0;
}
```

The issue was that the `_archive_entry_acl_text_l` function was not declared in the `libarchive` header file. To fix this, the `archive_entry_acl_text_l` function was used instead.