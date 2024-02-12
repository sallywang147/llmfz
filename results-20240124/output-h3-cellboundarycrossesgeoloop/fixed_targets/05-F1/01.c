#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "geo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct GeoLoop geoloop;
  struct BBox loopBBox;
  struct CellBoundary boundary;
  struct BBox boundaryBBox;

  memset(&geoloop, 0, sizeof(struct GeoLoop));
  memset(&loopBBox, 0, sizeof(struct BBox));
  memset(&boundary, 0, sizeof(struct CellBoundary));
  memset(&boundaryBBox, 0, sizeof(struct BBox));

  geoloop.num_cells = stream.ConsumeIntegral<int32_t>();
  geoloop.cells = reinterpret_cast<struct Cell*>(
      malloc(geoloop.num_cells * sizeof(struct Cell)));
  for (int32_t i = 0; i < geoloop.num_cells; i++) {
    geoloop.cells[i].index = stream.ConsumeIntegral<int64_t>();
    geoloop.cells[i].boundary = stream.ConsumeIntegral<int32_t>();
  }

  loopBBox.min_x = stream.ConsumeFloatingPoint<double>();
  loopBBox.min_y = stream.ConsumeFloatingPoint<double>();
  loopBBox.max_x = stream.ConsumeFloatingPoint<double>();
  loopBBox.max_y = stream.ConsumeFloatingPoint<double>();

  boundary.index = stream.ConsumeIntegral<int64_t>();
  boundary.edge = stream.ConsumeIntegral<int32_t>();
  boundary.start_vertex = stream.ConsumeIntegral<int32_t>();
  boundary.end_vertex = stream.ConsumeIntegral<int32_t>();

  boundaryBBox.min_x = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.min_y = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.max_x = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.max_y = stream.ConsumeFloatingPoint<double>();

  cellBoundaryCrossesGeoLoop(&geoloop, &loopBBox, &boundary, &boundaryBBox);

  free(geoloop.cells);
  return 0;
}