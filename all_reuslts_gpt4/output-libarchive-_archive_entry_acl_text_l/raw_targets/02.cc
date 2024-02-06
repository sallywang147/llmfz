#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"
#include "archive_entry.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct archive_entry *entry = archive_entry_new();
  if (entry == nullptr) {
    return 0;
  }

  int flags = stream.ConsumeIntegral<int>();
  char *acl_text = nullptr;
  size_t len = 0;
  struct archive_string_conv *sc = nullptr;

  int ret = _archive_entry_acl_text_l(entry, flags, &acl_text, &len, sc);

  if (ret == ARCHIVE_OK) {
    free(acl_text);
  }

  archive_entry_free(entry);

  return 0;
}