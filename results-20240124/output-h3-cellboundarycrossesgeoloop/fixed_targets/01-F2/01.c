#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "geo/geoloop.h"
#include "geo/bbox.h"
#include "geo/cellboundary.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct GeoLoop geoloop;
  struct BBox loopBBox;
  struct CellBoundary boundary;
  struct BBox boundaryBBox;
  cellBoundaryCrossesGeoLoop(&geoloop, &loopBBox, &boundary, &boundaryBBox);
  return 0;
}