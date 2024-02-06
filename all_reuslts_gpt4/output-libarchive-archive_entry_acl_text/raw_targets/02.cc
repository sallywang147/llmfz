#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"
#include "archive_entry.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct archive *a;
  struct archive_entry *entry;
  int r;

  a = archive_read_new();
  archive_read_support_format_all(a);
  archive_read_support_filter_all(a);
  r = archive_read_open_memory(a, data, size);
  if (r != ARCHIVE_OK)
    return 0;
  
  while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
    FuzzedDataProvider stream(data, size);
    int flags = stream.ConsumeIntegral<int>();
    char *acl_text = archive_entry_acl_text(entry, flags);
    if(acl_text != NULL) {
      free(acl_text);
    }
    archive_read_data_skip(a);
  }
  
  r = archive_read_free(a);
  if (r != ARCHIVE_OK)
    return 0;

  return 0;
}