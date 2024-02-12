#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dwfl.h>
#include <vector>

extern "C" {
#include <algorithm>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int tid = stream.ConsumeIntegral<int>();
  dwfl_getthread_frames(nullptr, tid, nullptr, nullptr);
  return 0;
}