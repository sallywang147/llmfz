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

  // Initialize the cursor and reg_state with data from the fuzzer
  std::vector<uint8_t> cursor_data = stream.ConsumeBytes<uint8_t>(sizeof(cursor));
  std::memcpy(&cursor, cursor_data.data(), cursor_data.size());

  std::vector<uint8_t> reg_state_data = stream.ConsumeBytes<uint8_t>(sizeof(reg_state));
  std::memcpy(&reg_state, reg_state_data.data(), reg_state_data.size());

  // Call the function under test
  _ULx86_64_dwarf_apply_reg_state(&cursor, &reg_state);

  return 0;
}