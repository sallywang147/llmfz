 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <dwarfdump.h>
#include <libdwarf.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwarf_Debug dbg = nullptr;
  if (dwarf_init(&dbg, DWARF_C_READ, nullptr, nullptr, nullptr) != DW_DLV_OK) {
    return 0;
  }

  Dwarf_Addr base_address = stream.ConsumeIntegral<Dwarf_Addr>();
  Dwarf_Die die = stream.ConsumeIntegral<Dwarf_Die>();
  Dwarf_Frame_Op* ops = nullptr;
  Dwarf_Signed ops_count = 0;
  Dwarf_Error error = dwarf_get_frame_instructions(
      dbg, base_address, die, &ops, &ops_count, nullptr);
  if (error != DW_DLV_OK) {
    dwarf_finish(dbg, nullptr);
    return 0;
  }

  Dwarf_Frame frame;
  if (dwarf_frame_init(&frame, dbg, base_address, die, ops, ops_count) !=
      DW_DLV_OK) {
    dwarf_free(dbg, ops, DW_DLA_FRAME_BLOCK);
    dwarf_finish(dbg, nullptr);
    return 0;
  }

  size_t pc = 0;
  char is_activation = 0;
  dwfl_frame_pc(&frame, &pc, &is_activation);

  dwarf_free(dbg, ops, DW_DLA_FRAME_BLOCK);
  dwarf_finish(dbg, nullptr);

  return 0;
}