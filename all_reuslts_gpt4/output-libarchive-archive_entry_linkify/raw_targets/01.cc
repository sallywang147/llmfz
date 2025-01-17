#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"
#include "archive_entry.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct archive_entry_linkresolver *res = archive_entry_linkresolver_new();
  if (res == nullptr) {
    return 0;
  }

  struct archive_entry *entry1 = archive_entry_new();
  struct archive_entry *entry2 = archive_entry_new();
  if (entry1 == nullptr || entry2 == nullptr) {
    archive_entry_linkresolver_free(res);
    archive_entry_free(entry1);
    archive_entry_free(entry2);
    return 0;
  }

  // Initialize entries with random data
  archive_entry_set_pathname(entry1, provider.ConsumeRandomLengthString().c_str());
  archive_entry_set_pathname(entry2, provider.ConsumeRandomLengthString().c_str());

  struct archive_entry *e = entry1;
  struct archive_entry *f = entry2;

  // Call the function to fuzz
  archive_entry_linkify(res, &e, &f);

  // Clean up
  archive_entry_linkresolver_free(res);
  archive_entry_free(entry1);
  archive_entry_free(entry2);

  return 0;
}