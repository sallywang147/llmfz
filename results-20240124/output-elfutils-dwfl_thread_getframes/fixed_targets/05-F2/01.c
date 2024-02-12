#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <libdwarf.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwfl_Thread thread = {0};
  dwfl_thread_init(&thread, 0);

  dwfl_thread_getframes(&thread, nullptr, nullptr);
  dwfl_thread_destroy(&thread);

  return 0;
}