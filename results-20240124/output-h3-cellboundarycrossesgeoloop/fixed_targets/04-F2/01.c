#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

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
  geoloop.num_vertices = stream.ConsumeIntegral<uint16_t>();
  geoloop.vertices = static_cast<struct GeoVertex*>(
      malloc(sizeof(struct GeoVertex) * geoloop.num_vertices));
  for (uint16_t i = 0; i < geoloop.num_vertices; ++i) {
    geoloop.vertices[i].x = stream.ConsumeIntegral<float>();
    geoloop.vertices[i].y = stream.ConsumeIntegral<float>();
  }

  struct BBox loop_bbox;
  loop_bbox.min_x = stream.ConsumeIntegral<float>();
  loop_bbox.min_y = stream.ConsumeIntegral<float>();
  loop_bbox.max_x = stream.ConsumeIntegral<float>();
  loop_bbox.max_y = stream.ConsumeIntegral<float>();

  struct CellBoundary boundary;
  boundary.start_x = stream.ConsumeIntegral<float>();
  boundary.start_y = stream.ConsumeIntegral<float>();
  boundary.end_x = stream.ConsumeIntegral<float>();
  boundary.end_y = stream.ConsumeIntegral<float>();

  struct BBox boundary_bbox;
  boundary_bbox.min_x = stream.ConsumeIntegral<float>();
  boundary_bbox.min_y = stream.ConsumeIntegral<float>();
  boundary_bbox.max_x = stream.ConsumeIntegral<float>();
  boundary_bbox.max_y = stream.ConsumeIntegral<float>();

  cellBoundaryCrossesGeoLoop(&geoloop, &loop_bbox, &boundary, &boundary_bbox);

  free(geoloop.vertices);

  return 0;
}