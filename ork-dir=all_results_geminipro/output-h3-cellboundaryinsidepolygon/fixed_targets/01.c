#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cell_boundary.h"
#include "geo_polygon.h"

extern "C" {
#include "cell_boundary_inside_polygon.h"
}

bool cellBoundaryInsidePolygon(const GeoPolygon* geo_polygon, const BBox* bbox,
                               const CellBoundary* boundary,
                               const BBox* boundary_bbox);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a GeoPolygon object.
  size_t num_vertices = provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<double> vertices(num_vertices * 2);
  for (size_t i = 0; i < num_vertices; i++) {
    vertices[2 * i] = provider.ConsumeFloatingPoint<double>();
    vertices[2 * i + 1] = provider.ConsumeFloatingPoint<double>();
  }
  GeoPolygon geo_polygon(vertices);

  // Create a BBox object.
  double min_x = provider.ConsumeFloatingPoint<double>();
  double min_y = provider.ConsumeFloatingPoint<double>();
  double max_x = provider.ConsumeFloatingPoint<double>();
  double max_y = provider.ConsumeFloatingPoint<double>();
  BBox bbox(min_x, min_y, max_x, max_y);

  // Create a CellBoundary object.
  double start_x = provider.ConsumeFloatingPoint<double>();
  double start_y = provider.ConsumeFloatingPoint<double>();
  double end_x = provider.ConsumeFloatingPoint<double>();
  double end_y = provider.ConsumeFloatingPoint<double>();
  CellBoundary boundary(start_x, start_y, end_x, end_y);

  // Create a BBox object for the boundary.
  BBox boundary_bbox(start_x, start_y, end_x, end_y);

  // Call the function to be fuzzed.
  bool result = cellBoundaryInsidePolygon(&geo_polygon, &bbox, &boundary,
                                         &boundary_bbox);

  return 0;
}