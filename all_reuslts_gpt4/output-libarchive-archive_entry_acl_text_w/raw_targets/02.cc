#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "archive.h"
#include "archive_entry.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new archive entry
  struct archive_entry *entry = archive_entry_new();
  if (entry == nullptr) {
    return 0;
  }

  // Use the fuzzed data to set the ACL text
  std::string acl_text = stream.ConsumeRemainingBytesAsString();
  archive_entry_acl_add_entry(entry, ARCHIVE_ENTRY_ACL_TYPE_ALLOW, 1001, ARCHIVE_ENTRY_ACL_EXECUTE, ARCHIVE_ENTRY_ACL_USER, acl_text.c_str());

  // Consume a flag from the fuzzed data
  int flags = stream.ConsumeIntegral<int>();

  // Call the target function
  archive_entry_acl_text_w(entry, flags);

  // Clean up
  archive_entry_free(entry);

  return 0;
}