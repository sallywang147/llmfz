#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Dwarf_Debug structure
  Dwarf_Debug_s dbg;
  dbg.de_pointer_size = stream.ConsumeIntegral<unsigned char>();
  dbg.de_offset_size = stream.ConsumeIntegral<unsigned char>();
  dbg.de_version_magic_number = stream.ConsumeIntegral<unsigned short>();
  dbg.de_length_size = stream.ConsumeIntegral<unsigned char>();
  dbg.de_64bit_extension = stream.ConsumeIntegral<unsigned char>();

  // Initialize the Dwarf_Rnglists_Head_s structure
  Dwarf_Rnglists_Head_s rctx;
  rctx.rl_bytecount = stream.ConsumeIntegral<Dwarf_Unsigned>();
  rctx.rl_version = stream.ConsumeIntegral<Dwarf_Small>();
  rctx.rl_offset_entrycount = stream.ConsumeIntegral<Dwarf_Unsigned>();
  rctx.rl_bytes_total = stream.ConsumeIntegral<Dwarf_Unsigned>();

  // Initialize the Dwarf_Error_s structure
  Dwarf_Error_s error;
  error.er_errval = stream.ConsumeIntegral<Dwarf_Signed>();
  error.er_static_alloc = stream.ConsumeBool();

  // Call the target function
  build_array_of_rle(&dbg, &rctx, &error);

  return 0;
}