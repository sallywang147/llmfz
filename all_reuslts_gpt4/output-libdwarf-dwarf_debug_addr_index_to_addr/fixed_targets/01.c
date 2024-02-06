#include <fuzzer/FuzzedDataProvider.h>
#include <libdwarf/dwarf.h>
#include <libdwarf/libdwarf.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a Dwarf_Debug object
  Dwarf_Debug dbg;
  int res = dwarf_init(-1, DW_DLC_READ, 0, 0, &dbg, 0);
  if (res != DW_DLV_OK) {
    return 0;
  }

  // Create a Dwarf_Die object
  Dwarf_Die die;
  res = dwarf_siblingof(dbg, NULL, &die, 0);
  if (res != DW_DLV_OK) {
    dwarf_finish(dbg, 0);
    return 0;
  }

  // Get index from the stream
  size_t index = stream.ConsumeIntegral<size_t>();

  // Initialize return_addr and error
  size_t return_addr = 0;
  Dwarf_Error error = 0;

  // Call the function
  dwarf_debug_addr_index_to_addr(&die, index, &return_addr, &error);

  // Clean up
  dwarf_dealloc(dbg, die, DW_DLA_DIE);
  dwarf_finish(dbg, 0);

  return 0;
}