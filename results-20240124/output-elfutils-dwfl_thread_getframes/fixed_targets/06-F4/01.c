#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "libdwarf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int fd = stream.ConsumeIntegral<int>();
  const char *path = stream.ConsumeRandomLengthString().c_str();
  const char *section = stream.ConsumeRandomLengthString().c_str();
  const char *error = stream.ConsumeRandomLengthString().c_str();
  const char *arg = stream.ConsumeRandomLengthString().c_str();
  struct Dwfl_Thread thread;
  dwfl_thread_init(&thread, fd, path, section, error);
  dwfl_thread_getframes(&thread, nullptr, const_cast<char*>(arg));
  dwfl_thread_destroy(&thread);
  return 0;
}