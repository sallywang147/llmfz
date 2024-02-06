#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "GeoLoop.h"

extern "C" {
#include "cellBoundaryCrossesGeoLoop.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct GeoLoop geoloop;
  struct BBox loopBBox;
  struct CellBoundary boundary;
  struct BBox boundaryBBox;

  provider.ConsumeBytes(&geoloop, sizeof(geoloop));
  provider.ConsumeBytes(&loopBBox, sizeof(loopBBox));
  provider.ConsumeBytes(&boundary, sizeof(boundary));
  provider.ConsumeBytes(&boundaryBBox, sizeof(boundaryBBox));

  int result = cellBoundaryCrossesGeoLoop(&geoloop, &loopBBox, &boundary, &boundaryBBox);

  return result;
}