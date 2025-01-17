#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "cell_boundary.h"
#include "geo_polygon.h"
#include "geo_types.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const uint32_t num_bboxes = stream.ConsumeIntegral<uint32_t>();
  std::vector<BBox> bboxes(num_bboxes);
  for (uint32_t i = 0; i < num_bboxes; ++i) {
    bboxes[i].min_x = stream.ConsumeIntegral<double>();
    bboxes[i].max_x = stream.ConsumeIntegral<double>();
    bboxes[i].min_y = stream.ConsumeIntegral<double>();
    bboxes[i].max_y = stream.ConsumeIntegral<double>();
  }

  CellBoundary boundary;
  boundary.cell_id = stream.ConsumeIntegral<uint64_t>();
  boundary.edge_index = stream.ConsumeIntegral<uint32_t>();
  boundary.vertex_index = stream.ConsumeIntegral<uint32_t>();

  GeoPolygon geo_polygon;
  geo_polygon.num_vertices = stream.ConsumeIntegral<uint32_t>();
  geo_polygon.vertices = new GeoVertex[geo_polygon.num_vertices];
  for (uint32_t i = 0; i < geo_polygon.num_vertices; ++i) {
    geo_polygon.vertices[i].x = stream.ConsumeIntegral<double>();
    geo_polygon.vertices[i].y = stream.ConsumeIntegral<double>();
  }

  BBox boundary_bbox;
  boundary_bbox.min_x = stream.ConsumeIntegral<double>();
  boundary_bbox.max_x = stream.ConsumeIntegral<double>();
  boundary_bbox.min_y = stream.ConsumeIntegral<double>();
  boundary_bbox.max_y = stream.ConsumeIntegral<double>();

  cellBoundaryInsidePolygon(&geo_polygon, bboxes.data(), &boundary, &boundary_bbox);

  delete[] geo_polygon.vertices;

  return 0;
}