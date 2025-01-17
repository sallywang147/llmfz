#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libunwind.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dwarf_cursor cursor;
  struct dwarf_reg_state reg_state;

  // Initialize the cursor and reg_state with fuzzed data
  size_t consumed = stream.ConsumeData(&cursor, sizeof(cursor));
  if (consumed != sizeof(cursor)) {
    return 0;
  }

  consumed = stream.ConsumeData(&reg_state, sizeof(reg_state));
  if (consumed != sizeof(reg_state)) {
    return 0;
  }

  // Call the function to fuzz
  _ULx86_64_dwarf_apply_reg_state(&cursor, &reg_state);

  return 0;
}