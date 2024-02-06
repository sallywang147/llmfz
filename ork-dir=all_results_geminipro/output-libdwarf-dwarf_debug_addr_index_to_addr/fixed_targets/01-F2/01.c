#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <dwarf.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwarf_Debug dbg;
  Dwarf_Error err;
  int res = dwarf_init(&dbg, DWARF_C_READ, DWARF_NULL, 0, &err);
  if (res != DW_DLV_OK) {
    return 0;
  }

  Dwarf_Die die;
  dwarf_get_DIE(dbg, stream.ConsumeIntegral<Dwarf_Off>(), &die, &err); // Added closing parenthesis

  size_t index = stream.ConsumeIntegral<size_t>();
  size_t return_addr;

  res = dwarf_debug_addr_index_to_addr(&die, index, &return_addr, &err);
  if (res == DW_DLV_ERROR) {
    dwarf_dealloc(dbg, die, DW_DLA_DIE);
    dwarf_finish(dbg, &err);
    return 0;
  }

  dwarf_dealloc(dbg, die, DW_DLA_DIE);
  dwarf_finish(dbg, &err);
  return 0;
}