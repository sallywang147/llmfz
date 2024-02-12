#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "libdwarf.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* path = stream.ConsumeRandomLengthString().c_str();
  const int tid = stream.ConsumeIntegral<int>();
  const char* arg = stream.ConsumeRandomLengthString().c_str();

  struct Dwfl* dwfl = dwfl_begin(path);
  if (dwfl == nullptr) {
    return 0;
  }

  dwfl_getthread_frames(dwfl, tid, nullptr, (char*)arg);

  dwfl_end(dwfl);
  return 0;
}