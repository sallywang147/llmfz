#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <vector>

#include "archive.h"

extern "C" {
#include <libarchive/archive.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  int ret;
  struct archive *a = archive_read_new();
  struct archive_entry *e, *f;
  struct archive_entry_linkresolver *res = archive_entry_linkresolver_new();

  archive_read_support_filter_all(a);
  archive_read_support_format_all(a);

  std::vector<uint8_t> data_buffer(getpagesize(), 0);
  Buffer buffer = {buf, len};
  archive_read_open(a, &buffer, NULL, reader_callback, NULL);

  while (1) {
    ret = archive_read_next_header(a, &e);
    if (ret == ARCHIVE_EOF || ret == ARCHIVE_FATAL)
      break;
    if (ret == ARCHIVE_RETRY)
      continue;
    while ((r = archive_read_data(a, data_buffer.data(), data_buffer.size())) > 0)
      ;
    if (r == ARCHIVE_FATAL)
      break;
  }

  archive_entry_linkify(res, &e, &f);

  archive_entry_linkresolver_free(res);
  archive_read_free(a);
  return 0;
}

static ssize_t reader_callback(struct archive *a, void *client_data, const void **buf) {
  Buffer *buffer = (Buffer *)client_data;
  *buf = buffer->buf;
  return buffer->len;
}