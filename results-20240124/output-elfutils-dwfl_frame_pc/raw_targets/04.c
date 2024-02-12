 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  Dwarf_Debug dbg;
  int fd = provider.ConsumeIntegralInRange<int>(0, 100000);
  if (dwfl_linux_proc_read_begin(&dbg, fd, 0, 0) != DW_DLV_OK) {
    return 0;
  }
  size_t pc = provider.ConsumeIntegral<size_t>();
  char isactivation = provider.ConsumeIntegral<char>();
  dwfl_frame_pc(nullptr, &pc, &isactivation);
  dwfl_linux_proc_read_end(&dbg);
  return 0;
}