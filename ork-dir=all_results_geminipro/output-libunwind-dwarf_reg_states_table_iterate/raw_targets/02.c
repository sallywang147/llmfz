#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string dwarf_data = stream.ConsumeRemainingBytesAsString();

  Dwarf_Debug dbg;
  Dwarf_Error err;
  int res = dwarf_init(dwarf_data.c_str(), DW_DLC_READ, &dbg, &err);
  if (res != DW_DLV_OK) {
    return 0;
  }

  Dwarf_Cursor cursor;
  Dwarf_Addr bias;
  res = dwarf_init_cursor(&cursor, dbg, bias, &err);
  if (res != DW_DLV_OK) {
    dwarf_finish(dbg, &err);
    return 0;
  }

  Dwarf_Regtable_Entry entry;
  Dwarf_Off offset;
  Dwarf_Unsigned reg_num;
  Dwarf_Unsigned reg_type;
  Dwarf_Unsigned reg_size;
  Dwarf_Unsigned reg_offset;
  Dwarf_Unsigned reg_bit_offset;
  Dwarf_Unsigned reg_bit_size;
  Dwarf_Unsigned reg_flags;

  res = dwarf_reg_states_table_iterate(
      &cursor,
      [](Dwarf_Regtable_Entry* entry, void* token) {
        Dwarf_Unsigned reg_num = entry->reg_num;
        Dwarf_Unsigned reg_type = entry->reg_type;
        Dwarf_Unsigned reg_size = entry->reg_size;
        Dwarf_Unsigned reg_offset = entry->reg_offset;
        Dwarf_Unsigned reg_bit_offset = entry->reg_bit_offset;
        Dwarf_Unsigned reg_bit_size = entry->reg_bit_size;
        Dwarf_Unsigned reg_flags = entry->reg_flags;
        return DW_DLV_OK;
      },
      nullptr);
  if (res != DW_DLV_OK) {
    dwarf_finish(dbg, &err);
    return 0;
  }

  dwarf_finish(dbg, &err);
  return 0;
}