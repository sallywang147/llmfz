#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cell_boundary.h"
#include "geo_polygon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider data_provider(data, size);
  // Parse the input data as a GeoPolygon.
  GeoPolygon geo_polygon;
  size_t num_vertices = data_provider.ConsumeIntegralInRange<size_t>(0, 100);
  for (size_t i = 0; i < num_vertices; ++i) {
    double x = data_provider.ConsumeFloatingPoint<double>();
    double y = data_provider.ConsumeFloatingPoint<double>();
    geo_polygon.AddVertex(x, y);
  }

  // Parse the input data as an array of BBoxes.
  size_t num_bboxes = data_provider.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<BBox> bboxes;
  for (size_t i = 0; i < num_bboxes; ++i) {
    double min_x = data_provider.ConsumeFloatingPoint<double>();
    double min_y = data_provider.ConsumeFloatingPoint<double>();
    double max_x = data_provider.ConsumeFloatingPoint<double>();
    double max_y = data_provider.ConsumeFloatingPoint<double>();
    bboxes.emplace_back(min_x, min_y, max_x, max_y);
  }

  // Parse the input data as a CellBoundary.
  CellBoundary boundary;
  double start_x = data_provider.ConsumeFloatingPoint<double>();
  double start_y = data_provider.ConsumeFloatingPoint<double>();
  double end_x = data_provider.ConsumeFloatingPoint<double>();
  double end_y = data_provider.ConsumeFloatingPoint<double>();
  boundary.SetStart(start_x, start_y);
  boundary.SetEnd(end_x, end_y);

  // Parse the input data as a BBox for the boundary.
  BBox boundary_bbox;
  double boundary_min_x = data_provider.ConsumeFloatingPoint<double>();
  double boundary_min_y = data_provider.ConsumeFloatingPoint<double>();
  double boundary_max_x = data_provider.ConsumeFloatingPoint<double>();
  double boundary_max_y = data_provider.ConsumeFloatingPoint<double>();
  boundary_bbox.SetMin(boundary_min_x, boundary_min_y);
  boundary_bbox.SetMax(boundary_max_x, boundary_max_y);

  // Call the function to be fuzzed.
  bool result = cellBoundaryCrossesPolygon(&geo_polygon, bboxes.data(), &boundary,
                                          &boundary_bbox);

  return 0;
}