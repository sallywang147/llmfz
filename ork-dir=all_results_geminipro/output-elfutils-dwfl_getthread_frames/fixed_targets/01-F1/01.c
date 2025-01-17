#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <libdwarf.h>

extern "C" {
#include <libdwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    dwfl_linux_init();
    initialized = true;
  }
  int ret;
  struct Dwfl* dwfl = dwfl_begin(&ret);
  if (dwfl == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  int tid = provider.ConsumeIntegral<int>();
  func_type callback =
      [](void* arg, const char* name, const char* file, int line, int column) {
        return 0;
      };
  char* arg = nullptr;

  ret = dwfl_getthread_frames(dwfl, tid, callback, arg);

  dwfl_end(dwfl);

  return 0;
}