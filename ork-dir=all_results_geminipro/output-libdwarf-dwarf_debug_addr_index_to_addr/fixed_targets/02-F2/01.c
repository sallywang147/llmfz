#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "dwarf.h"

extern "C" {
#include <libdwarf/dwarf.h>
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  size_t die_offset = fdp.ConsumeIntegralInRange<size_t>(0, 10000);
  size_t index = fdp.ConsumeIntegralInRange<size_t>(0, 10000);
  size_t return_addr;
  Dwarf_Error_s* error;
  dwarf_debug_addr_index_to_addr(nullptr, die_offset, index, &return_addr, &error);
  return 0;
}
}