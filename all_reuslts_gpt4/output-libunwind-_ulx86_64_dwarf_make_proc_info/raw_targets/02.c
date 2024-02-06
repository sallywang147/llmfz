#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "libunwind.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a struct dwarf_cursor
  struct dwarf_cursor cursor;

  // Initialize struct members with fuzzed data
  cursor.loc = stream.ConsumeIntegral<uint64_t>();
  cursor.ip = stream.ConsumeIntegral<uint64_t>();
  cursor.cfa = stream.ConsumeIntegral<uint64_t>();
  cursor.ret_addr_column = stream.ConsumeIntegral<int>();
  cursor.pi_valid = stream.ConsumeBool();
  cursor.use_prev_instr = stream.ConsumeBool();

  // Call the function to fuzz
  _ULx86_64_dwarf_make_proc_info(&cursor);

  return 0;
}