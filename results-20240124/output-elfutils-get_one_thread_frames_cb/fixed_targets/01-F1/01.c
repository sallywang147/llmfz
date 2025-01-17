#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* filename = stream.ConsumeRandomLengthString().c_str();
  Dwarf_Debug dbg;
  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    return 0;
  }
  if (dwarf_init(fd, DW_DLC_READ, &dbg) != DW_DLV_OK) {
    return 0;
  }
  Dwarf_Addr base_addr = stream.ConsumeIntegral<Dwarf_Addr>();
  Dwarf_Addr offset = stream.ConsumeIntegral<Dwarf_Addr>();
  Dwarf_Die die;
  Dwarf_Error err;
  if (dwarf_addrdie_b(dbg, base_addr, &die, &err) != DW_DLV_OK) {
    return 0;
  }
  dwarf_get_die_infotypes_flag(die, &err);
  dwarf_get_die_threads_flag(die, &err);
  Dwarf_Thread* thread = dwarf_get_threads(dbg, &err);
  if (thread == nullptr) {
    return 0;
  }
  get_one_thread_frames_cb(thread, nullptr);
  dwarf_free(dbg, thread);
  dwarf_finish(dbg, &err);
  return 0;
}