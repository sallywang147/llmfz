#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "libdwarf.h"

extern "C" {
#include "libdwarf_arm.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint32_t cursor_version = stream.ConsumeIntegral<uint32_t>();
  const uint32_t reg_state_version = stream.ConsumeIntegral<uint32_t>();

  // Fix the function name to match the header
  Dwarf_Cursor* cursor = dwarf_cursor_new(cursor_version, 0);
  if (cursor == nullptr) {
    return 0;
  }
  Dwarf_Reg_State* reg_state = dwarf_reg_state_new(reg_state_version, 0);
  if (reg_state == nullptr) {
    dwarf_cursor_free(cursor);
    return 0;
  }

  const uint8_t* reg_state_data = stream.ConsumeRemainingBytes();
  const size_t reg_state_data_size = stream.ConsumeIntegralInRange<size_t>(
      0, stream.remaining_bytes());
  if (dwarf_reg_state_read(reg_state, reg_state_data, reg_state_data_size) !=
      DW_DLV_OK) {
    dwarf_reg_state_free(reg_state);
    dwarf_cursor_free(cursor);
    return 0;
  }

  // Fix the function name to match the header
  const int result = dwarf_apply_reg_state(cursor, reg_state);
  dwarf_reg_state_free(reg_state);
  dwarf_cursor_free(cursor);
  return result;
}