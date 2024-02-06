#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libdwarf/dwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Dwarf_Debug dbg;
  if (dwarf_init(&dbg, DWARF_C_READ, nullptr, nullptr, nullptr) != DW_DLV_OK) {
    return 0;
  }
  Dwarf_Sig8 ref;
  ref.signature = stream.ConsumeIntegral<Dwarf_Sig8::signature_type>();
  ref.type = stream.ConsumeIntegral<Dwarf_Sig8::type_type>();
  Dwarf_Die* die_out;
  int is_info;
  Dwarf_Error* error;
  if (dwarf_find_die_given_sig8(&dbg, &ref, &die_out, &is_info, &error) !=
      DW_DLV_OK) {
    dwarf_finish(&dbg);
    return 0;
  }
  dwarf_dealloc(dbg, die_out, DW_DLA_DIE);
  dwarf_finish(&dbg);
  return 0;
}