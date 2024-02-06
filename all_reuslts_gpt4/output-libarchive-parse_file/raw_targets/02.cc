#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"
#include "archive_entry.h"
#include "archive_private.h"
#include "archive_read_private.h"

struct mtree {
  int dummy;
};

struct mtree_entry {
  int dummy;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  struct archive_read* a = archive_read_new();
  struct archive_entry* entry = archive_entry_new();
  struct mtree* mtree = new mtree;
  struct mtree_entry* mentry = new mtree_entry;
  int use_next = fuzzed_data.ConsumeIntegral<int>();

  parse_file(a, entry, mtree, mentry, &use_next);

  archive_entry_free(entry);
  archive_read_free(a);
  delete mtree;
  delete mentry;

  return 0;
}