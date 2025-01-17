#include <libdwarf.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libdwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwarf_Debug dbg;
  int res = dwarf_init(&dbg, DWARF_C_READ, nullptr, nullptr, nullptr);
  if (res != DW_DLV_OK) {
    return 0;
  }

  Dwarf_Sig8 ref;
  stream.ConsumeData(&ref, sizeof(ref));

  Dwarf_Die die;
  int is_info;
  Dwarf_Error error;
  res = dwarf_find_die_given_sig8(&dbg, &ref, &die, &is_info, &error);
  if (res == DW_DLV_OK) {
    dwarf_dealloc(dbg, die, DW_DLA_DIE);
  }
  dwarf_finish(&dbg);
  return 0;
}