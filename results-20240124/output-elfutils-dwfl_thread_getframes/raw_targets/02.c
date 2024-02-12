 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *arg = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 256)).c_str();
  dwfl_thread_getframes(nullptr, nullptr, arg);
  return 0;
}