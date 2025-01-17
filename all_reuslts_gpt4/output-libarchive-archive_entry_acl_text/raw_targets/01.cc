#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <archive.h>
#include <archive_entry.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct archive_entry* entry = archive_entry_new();
  if (entry == nullptr) {
    return 0;
  }

  int flags = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  char* acl_text = archive_entry_acl_text(entry, flags);

  // Free the allocated memory
  archive_entry_free(entry);
  free(acl_text);

  return 0;
}