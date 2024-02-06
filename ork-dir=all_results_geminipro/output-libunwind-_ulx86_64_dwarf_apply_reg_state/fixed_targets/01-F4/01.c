#include <libdwarf.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <dwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwarf_Debug dbg = dwarf_begin();
  if (dbg == NULL) {
    return 0;
  }

  Dwarf_Cursor cursor;
  dwarf_init_cursor(dbg, &cursor, DW_DLC_LOCAL, 0, 0);

  Dwarf_Reg_State reg_state;
  dwarf_get_reg_state(&cursor, &reg_state);

  // Fix: Include the missing header
  #include <x86-64-dwarf.h>

  // Fix: Call the missing function
  _ULx86_64_dwarf_apply_reg_state(&cursor, &reg_state);

  dwarf_finish(dbg, NULL);
  return 0;
}