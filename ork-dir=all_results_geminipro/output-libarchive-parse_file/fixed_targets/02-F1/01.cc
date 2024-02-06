#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "archive.h"
#include "archive_entry.h"
#include "mtree.h"

extern "C" {
#include "parse_file.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  int ret;
  struct archive *a = archive_read_new();
  struct archive_entry *entry = archive_entry_new();
  struct mtree *mtree = mtree_new();
  struct mtree_entry *mentry = mtree_entry_new();
  int use_next = 0;

  archive_read_support_filter_all(a);
  archive_read_support_format_all(a);

  std::vector<uint8_t> buffer(buf, buf + len);
  archive_read_open_memory(a, buffer.data(), buffer.size());

  while ((ret = archive_read_next_header(a, entry)) == ARCHIVE_OK) {
    parse_file(a, entry, mtree, mentry, &use_next);
  }

  archive_read_free(a);
  archive_entry_free(entry);
  mtree_free(mtree);
  mtree_entry_free(mentry);
  return 0;
}