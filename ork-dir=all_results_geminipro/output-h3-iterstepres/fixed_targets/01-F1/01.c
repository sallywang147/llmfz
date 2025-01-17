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
  int64_t dlevel;
  int64_t dres;
  int64_t ddx;
  int64_t ddy;
  int64_t ddz;
  int64_t dlevel2;
  int64_t dres2;
  int64_t ddx2;
  int64_t ddy2;
  int64_t ddz2;
  int64_t dlevel3;
  int64_t dres3;
  int64_t ddx3;
  int64_t ddy3;
  int64_t ddz3;
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
  itR.dlevel = provider.ConsumeIntegral<int64_t>();
  itR.dres = provider.ConsumeIntegral<int64_t>();
  itR.ddx = provider.ConsumeIntegral<int64_t>();
  itR.ddy = provider.ConsumeIntegral<int64_t>();
  itR.ddz = provider.ConsumeIntegral<int64_t>();
  itR.dlevel2 = provider.ConsumeIntegral<int64_t>();
  itR.dres2 = provider.ConsumeIntegral<int64_t>();
  itR.ddx2 = provider.ConsumeIntegral<int64_t>();
  itR.ddy2 = provider.ConsumeIntegral<int64_t>();
  itR.ddz2 = provider.ConsumeIntegral<int64_t>();
  itR.dlevel3 = provider.ConsumeIntegral<int64_t>();
  itR.dres3 = provider.ConsumeIntegral<int64_t>();
  itR.ddx3 = provider.ConsumeIntegral<int64_t>();
  itR.ddy3 = provider.ConsumeIntegral<int64_t>();
  itR.ddz3 = provider.ConsumeIntegral<int64_t>();

  iterStepRes(&itR);

  return 0;
}

int iterStepRes(IterCellsResolution* itR) {
  // Do something with itR
  return 0;
}