#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "libdwarf.h"

extern "C" {
#include "libdwarf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* thread_name = stream.ConsumeRandomLengthString().c_str();
  Dwfl_Thread thread;
  dwfl_thread_init(&thread, thread_name, nullptr);
  dwfl_thread_getframes(&thread, nullptr, nullptr);
  dwfl_thread_fini(&thread);
  return 0;
}