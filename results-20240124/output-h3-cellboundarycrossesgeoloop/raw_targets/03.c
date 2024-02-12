 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "cell_boundary.h"
#include "geo_loop.h"
#include "geo_types.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct GeoLoop geoloop;
  int num_cells = stream.ConsumeIntegral<int>();
  geoloop.cells =
      static_cast<struct Cell*>(malloc(sizeof(struct Cell) * num_cells));
  for (int i = 0; i < num_cells; i++) {
    geoloop.cells[i].bbox.min_x = stream.ConsumeIntegral<double>();
    geoloop.cells[i].bbox.min_y = stream.ConsumeIntegral<double>();
    geoloop.cells[i].bbox.max_x = stream.ConsumeIntegral<double>();
    geoloop.cells[i].bbox.max_y = stream.ConsumeIntegral<double>();
  }
  geoloop.num_cells = num_cells;
  geoloop.bbox.min_x = stream.ConsumeIntegral<double>();
  geoloop.bbox.min_y = stream.ConsumeIntegral<double>();
  geoloop.bbox.max_x = stream.ConsumeIntegral<double>();
  geoloop.bbox.max_y = stream.ConsumeIntegral<double>();

  struct BBox loop_bbox;
  loop_bbox.min_x = stream.ConsumeIntegral<double>();
  loop_bbox.min_y = stream.ConsumeIntegral<double>();
  loop_bbox.max_x = stream.ConsumeIntegral<double>();
  loop_bbox.max_y = stream.ConsumeIntegral<double>();

  struct CellBoundary boundary;
  boundary.cell_index = stream.ConsumeIntegral<int>();
  boundary.edge_index = stream.ConsumeIntegral<int>();
  boundary.bbox.min_x = stream.ConsumeIntegral<double>();
  boundary.bbox.min_y = stream.ConsumeIntegral<double>();
  boundary.bbox.max_x = stream.ConsumeIntegral<double>();
  boundary.bbox.max_y = stream.ConsumeIntegral<double>();

  struct BBox boundary_bbox;
  boundary_bbox.min_x = stream.ConsumeIntegral<double>();
  boundary_bbox.min_y = stream.ConsumeIntegral<double>();
  boundary_bbox.max_x = stream.ConsumeIntegral<double>();
  boundary_bbox.max_y = stream.ConsumeIntegral<double>();

  cellBoundaryCrossesGeoLoop(&geoloop, &loop_bbox, &boundary, &boundary_bbox);
  return 0;
}