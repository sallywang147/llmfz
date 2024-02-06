#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libdwarf.h"

extern "C" {
#include "libdwarf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    dwfl_linux_init_auto();
    initialized = true;
  }
  int ret;
  struct Dwfl* dwfl = dwfl_begin(&ret);
  if (dwfl == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  int tid = provider.ConsumeIntegral<int>();

  struct func_type {
    void (*callback)(void*, const char*, const char*, const char*, int, int,
                     int, int, int, int, int, int, int);
    void* arg;
  };

  func_type func_type = {nullptr, nullptr};
  dwfl_getthread_frames(dwfl, tid, &func_type.callback, func_type.arg);

  dwfl_end(dwfl);

  return 0;
}