#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "geo_polygon.h"
#include "geo_polygon_internal.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a GeoPolygon.
  const uint8_t num_vertices = stream.ConsumeIntegralInRange<uint8_t>(1, 10);
  std::vector<GeoPoint> vertices(num_vertices);
  for (uint8_t i = 0; i < num_vertices; i++) {
    vertices[i].x = stream.ConsumeIntegral<double>();
    vertices[i].y = stream.ConsumeIntegral<double>();
  }
  GeoPolygon geo_polygon;
  geo_polygon_init(&geo_polygon, vertices.data(), num_vertices);

  // Create a BBox.
  BBox bbox;
  bbox.min_x = stream.ConsumeIntegral<double>();
  bbox.min_y = stream.ConsumeIntegral<double>();
  bbox.max_x = stream.ConsumeIntegral<double>();
  bbox.max_y = stream.ConsumeIntegral<double>();

  // Create a CellBoundary.
  CellBoundary boundary;
  boundary.start_x = stream.ConsumeIntegral<double>();
  boundary.start_y = stream.ConsumeIntegral<double>();
  boundary.end_x = stream.ConsumeIntegral<double>();
  boundary.end_y = stream.ConsumeIntegral<double>();

  // Create a BBox for the boundary.
  BBox boundary_bbox;
  boundary_bbox.min_x = stream.ConsumeIntegral<double>();
  boundary_bbox.min_y = stream.ConsumeIntegral<double>();
  boundary_bbox.max_x = stream.ConsumeIntegral<double>();
  boundary_bbox.max_y = stream.ConsumeIntegral<double>();

  // Call the function.
  cellBoundaryInsidePolygon(&geo_polygon, &bbox, &boundary, &boundary_bbox);

  // Clean up.
  geo_polygon_destroy(&geo_polygon);

  return 0;
}