#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "libdwarf.h"

extern "C" {
#include "libdwarf/dwarf_rnglists.h"
#include "libdwarf/dwarf_util.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwarf_Debug dbg;
  Dwarf_Rnglists_Head rctx;
  Dwarf_Error* error = nullptr;

  Dwarf_Init(&dbg, DW_DLC_READ, nullptr, nullptr, nullptr);
  Dwarf_Set_Simple_File_Entry(&dbg, "fuzz.c", nullptr, nullptr, nullptr);
  Dwarf_Set_Current_Line_Info(&dbg, 1, nullptr);

  Dwarf_Add_Rnglists_Entry(&dbg, &rctx, DW_RLE_OFFSET, DW_RLE_LENGTH,
                           DW_RLE_OFFSET_ENTRY_COUNT, DW_RLE_LENGTH_ENTRY_COUNT,
                           DW_RLE_OFFSET_ADDR_SIZE, DW_RLE_LENGTH_ADDR_SIZE);

  Dwarf_Rnglist_Entry* entry = nullptr;
  while (stream.remaining_bytes()) {
    Dwarf_Add_Rnglists_Entry_Offset(&dbg, &rctx, entry,
                                   stream.ConsumeIntegral<Dwarf_Addr>());
    Dwarf_Add_Rnglists_Entry_Length(&dbg, &rctx, entry,
                                   stream.ConsumeIntegral<Dwarf_Addr>());
  }

  int ret = build_array_of_rle(&dbg, &rctx, &error);
  Dwarf_Fini(&dbg);
  return ret;
}