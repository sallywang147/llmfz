 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "GeoPolygon.h"
#include "BBox.h"
#include "CellBoundary.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int num_bboxes = stream.ConsumeIntegral<int>();
  const int num_boundaries = stream.ConsumeIntegral<int>();
  const int num_polys = stream.ConsumeIntegral<int>();
  std::vector<BBox> bboxes(num_bboxes);
  for (auto& bbox : bboxes) {
    bbox.min_x = stream.ConsumeIntegral<double>();
    bbox.max_x = stream.ConsumeIntegral<double>();
    bbox.min_y = stream.ConsumeIntegral<double>();
    bbox.max_y = stream.ConsumeIntegral<double>();
  }
  std::vector<CellBoundary> boundaries(num_boundaries);
  for (auto& boundary : boundaries) {
    boundary.x1 = stream.ConsumeIntegral<double>();
    boundary.y1 = stream.ConsumeIntegral<double>();
    boundary.x2 = stream.ConsumeIntegral<double>();
    boundary.y2 = stream.ConsumeIntegral<double>();
  }
  std::vector<GeoPolygon> polys(num_polys);
  for (auto& poly : polys) {
    const int num_vertices = stream.ConsumeIntegral<int>();
    std::vector<double> vertices(2 * num_vertices);
    for (auto& vertex : vertices) {
      vertex = stream.ConsumeIntegral<double>();
    }
    poly.setVertices(vertices);
  }

  for (const auto& boundary : boundaries) {
    for (const auto& poly : polys) {
      BBox boundary_bbox;
      cellBoundaryCrossesPolygon(&poly, bboxes.data(), &boundary, &boundary_bbox);
    }
  }

  return 0;
}