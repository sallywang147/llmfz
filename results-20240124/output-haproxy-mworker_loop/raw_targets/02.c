 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "mworker.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<char> buffer(stream.ConsumeIntegralInRange<size_t>(1024, 4096));
  memcpy(buffer.data(), data, size);

  struct mworker worker;
  mworker_init(&worker, buffer.data(), buffer.size());
  mworker_loop();
  mworker_fini(&worker);

  return 0;
}