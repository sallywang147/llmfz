#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

struct IterCellsResolution {
  int64_t x;
  int64_t y;
  int64_t z;
  int64_t level;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  IterCellsResolution itR;
  itR.x = stream.ConsumeIntegral<int64_t>();
  itR.y = stream.ConsumeIntegral<int64_t>();
  itR.z = stream.ConsumeIntegral<int64_t>();
  itR.level = stream.ConsumeIntegral<int64_t>();
  iterStepRes(&itR);
  return 0;
}

// Add the missing function declaration
extern "C" void iterStepRes(IterCellsResolution* itR);