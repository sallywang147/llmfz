 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "libdwarf/libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t slate_width = stream.ConsumeIntegral<uint8_t>();
  const uint8_t slate_height = stream.ConsumeIntegral<uint8_t>();
  Dwarf_Debug dbg = dwarf_begin(data, size, DW_DLC_READ);
  if (dbg == NULL) {
    return 0;
  }
  Dwarf_Frame_Op* ops = (Dwarf_Frame_Op*)malloc(slate_width * slate_height * sizeof(Dwarf_Frame_Op));
  Dwarf_Frame_Op* op = ops;
  for (size_t i = 0; i < slate_width * slate_height; ++i) {
    op->atom = DW_OP_reg0 + stream.ConsumeIntegral<uint8_t>();
    op->offset = stream.ConsumeIntegral<uint8_t>();
    op++;
  }
  Dwarf_Frame frame = {
      .cfa = 0,
      .pc = 0,
      .fbreg = 0,
      .cfa_set = false,
      .pc_set = false,
      .fbreg_set = false,
      .ops = ops,
      .nops = slate_width * slate_height,
  };
  __libdwfl_frame_unwind(&frame);
  free(ops);
  dwarf_end(dbg);
  return 0;
}