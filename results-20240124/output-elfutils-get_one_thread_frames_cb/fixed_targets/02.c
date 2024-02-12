#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>

#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

extern "C" {
#include <libdwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int fd = stream.ConsumeIntegral<int>();
  Dwarf_Debug dbg = dwarf_begin(fd, DWARF_C_READ, nullptr);
  if (dbg == nullptr) {
    return 0;
  }

  Dwarf_Addr base_address = stream.ConsumeIntegral<Dwarf_Addr>();
  Dwarf_Unsigned offset = stream.ConsumeIntegral<Dwarf_Unsigned>();
  Dwarf_Die die = dwarf_offdie(dbg, offset, base_address);
  if (die == nullptr) {
    dwarf_end(dbg);
    return 0;
  }

  Dwarf_Thread thread;
  int res = dwarf_get_threads(dbg, &thread, nullptr);
  if (res != DW_DLV_OK) {
    dwarf_end(dbg);
    return 0;
  }

  char arg[1024];
  get_one_thread_frames_cb(&thread, arg);

  dwarf_end(dbg);
  return 0;
}