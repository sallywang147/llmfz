#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libunwind.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a dwarf_cursor object
  struct dwarf_cursor cursor;
  memset(&cursor, 0, sizeof(cursor));

  // Fill the dwarf_cursor object with fuzzed data
  size_t consumed = stream.ConsumeData(&cursor, sizeof(cursor));
  if (consumed != sizeof(cursor)) {
    return 0;
  }

  // Call the target function
  _ULx86_64_dwarf_make_proc_info(&cursor);

  return 0;
}