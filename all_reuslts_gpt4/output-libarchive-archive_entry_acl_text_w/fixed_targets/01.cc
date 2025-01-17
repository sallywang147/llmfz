#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"
#include "archive_entry.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Create a new archive entry
  struct archive_entry *entry = archive_entry_new();
  if (entry == nullptr) {
    return 0;
  }

  // Consume data to set as ACL text
  std::string acl_text = fuzzed_data.ConsumeRandomLengthString();
  if (archive_entry_acl_from_text(entry, acl_text.c_str(), ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != ARCHIVE_OK) {
    archive_entry_free(entry);
    return 0;
  }

  // Consume remaining data as flags
  int flags = fuzzed_data.ConsumeIntegral<int>();

  // Call the target function
  archive_entry_acl_text_w(entry, flags);

  // Clean up
  archive_entry_free(entry);

  return 0;
}