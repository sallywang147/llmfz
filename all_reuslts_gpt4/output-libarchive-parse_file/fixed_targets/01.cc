#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"
#include "archive_entry.h"
#include "archive_read.h"
#include "mtree_private.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize archive_read
  struct archive_read* a = archive_read_new();
  if (!a) {
    return 0;
  }

  // Initialize archive_entry
  struct archive_entry* entry = archive_entry_new();
  if (!entry) {
    archive_read_free(a);
    return 0;
  }

  // Initialize mtree
  struct mtree* mtree = (struct mtree*)calloc(1, sizeof(struct mtree));
  if (!mtree) {
    archive_entry_free(entry);
    archive_read_free(a);
    return 0;
  }

  // Initialize mtree_entry
  struct mtree_entry* mentry = (struct mtree_entry*)calloc(1, sizeof(struct mtree_entry));
  if (!mentry) {
    free(mtree);
    archive_entry_free(entry);
    archive_read_free(a);
    return 0;
  }

  // Initialize use_next
  int use_next = stream.ConsumeIntegral<int>();

  // Call the target function
  parse_file(a, entry, mtree, mentry, &use_next);

  // Clean up
  free(mentry);
  free(mtree);
  archive_entry_free(entry);
  archive_read_free(a);

  return 0;
}