#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwarf_Debug dbg;
  Dwarf_Sig8 ref;
  Dwarf_Die die_out;
  int is_info;
  Dwarf_Error error;

  // Initialize the dbg
  int init_res = dwarf_init(dbg, DW_DLC_READ, nullptr, nullptr, &dbg, &error);
  if (init_res != DW_DLV_OK) {
    return 0;
  }

  // Consume data for ref
  for (int i = 0; i < 8; ++i) {
    if (stream.remaining_bytes() < 1) {
      dwarf_finish(dbg, &error);
      return 0;
    }
    ref.signature[i] = stream.ConsumeIntegral<uint8_t>();
  }

  // Call the function to fuzz
  int res = dwarf_find_die_given_sig8(&dbg, &ref, &die_out, &is_info, &error);

  // Cleanup
  dwarf_finish(dbg, &error);

  return 0;
}