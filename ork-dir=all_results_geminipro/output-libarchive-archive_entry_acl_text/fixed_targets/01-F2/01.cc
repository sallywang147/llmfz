#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <archive.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  int ret;
  ssize_t r;
  struct archive *a = archive_read_new();

  archive_read_support_filter_all(a);
  archive_read_support_format_all(a);

  Buffer buffer = {buf, len};
  archive_read_open(a, &buffer, NULL, reader_callback, NULL);

  std::vector<uint8_t> data_buffer(getpagesize(), 0);
  struct archive_entry *entry;
  while (1) {
    ret = archive_read_next_header(a, &entry);
    if (ret == ARCHIVE_EOF || ret == ARCHIVE_FATAL)
      break;
    if (ret == ARCHIVE_RETRY)
      continue;
    while ((r = archive_read_data(a, data_buffer.data(), data_buffer.size())) > 0)
      ;
    if (r == ARCHIVE_FATAL)
      break;

    char *acl_text = archive_entry_acl_text(entry, ARCHIVE_ENTRY_ACL_TYPE_ACCESS);
    if (acl_text != NULL)
      free(acl_text);
  }

  archive_read_free(a);
  return 0;
}