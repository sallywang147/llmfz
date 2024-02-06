#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

struct IterCellsResolution {
  int64_t x;
  int64_t y;
  int64_t z;
  int64_t level;
  int64_t res;
  int64_t dx;
  int64_t dy;
  int64_t dz;
  int64_t dr;
  int64_t dlevel;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  IterCellsResolution itR;
  itR.x = provider.ConsumeIntegral<int64_t>();
  itR.y = provider.ConsumeIntegral<int64_t>();
  itR.z = provider.ConsumeIntegral<int64_t>();
  itR.level = provider.ConsumeIntegral<int64_t>();
  itR.res = provider.ConsumeIntegral<int64_t>();
  itR.dx = provider.ConsumeIntegral<int64_t>();
  itR.dy = provider.ConsumeIntegral<int64_t>();
  itR.dz = provider.ConsumeIntegral<int64_t>();
  itR.dr = provider.ConsumeIntegral<int64_t>();
  itR.dlevel = provider.ConsumeIntegral<int64_t>();

  iterStepRes(&itR);

  return 0;
}