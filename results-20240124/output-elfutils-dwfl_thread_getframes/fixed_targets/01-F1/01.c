#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwfl_Thread thread;
  if (dwfl_thread_init(&thread, DWFL_VERSION, NULL) != 0) {
    return 0;
  }

  dwfl_thread_getframes(&thread, [](void* arg, Dwarf_Addr addr,
                                   const char* fname, Dwarf_Unsigned line,
                                   Dwarf_Unsigned column) {
    return 0;
  }, nullptr);

  dwfl_thread_destroy(&thread);
  return 0;
}