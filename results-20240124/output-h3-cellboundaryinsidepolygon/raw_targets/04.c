 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "geo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t num_bboxes = stream.ConsumeIntegralInRange<size_t>(0, 100);
  struct BBox* bboxes =
      static_cast<struct BBox*>(malloc(sizeof(struct BBox) * num_bboxes));
  for (size_t i = 0; i < num_bboxes; i++) {
    bboxes[i].minx = stream.ConsumeIntegral<double>();
    bboxes[i].miny = stream.ConsumeIntegral<double>();
    bboxes[i].maxx = stream.ConsumeIntegral<double>();
    bboxes[i].maxy = stream.ConsumeIntegral<double>();
  }

  const size_t num_boundaries = stream.ConsumeIntegralInRange<size_t>(0, 100);
  struct CellBoundary* boundaries =
      static_cast<struct CellBoundary*>(
          malloc(sizeof(struct CellBoundary) * num_boundaries));
  for (size_t i = 0; i < num_boundaries; i++) {
    boundaries[i].x1 = stream.ConsumeIntegral<double>();
    boundaries[i].y1 = stream.ConsumeIntegral<double>();
    boundaries[i].x2 = stream.ConsumeIntegral<double>();
    boundaries[i].y2 = stream.ConsumeIntegral<double>();
  }

  const size_t num_boundary_bboxes =
      stream.ConsumeIntegralInRange<size_t>(0, 100);
  struct BBox* boundary_bboxes =
      static_cast<struct BBox*>(
          malloc(sizeof(struct BBox) * num_boundary_bboxes));
  for (size_t i = 0; i < num_boundary_bboxes; i++) {
    boundary_bboxes[i].minx = stream.ConsumeIntegral<double>();
    boundary_bboxes[i].miny = stream.ConsumeIntegral<double>();
    boundary_bboxes[i].maxx = stream.ConsumeIntegral<double>();
    boundary_bboxes[i].maxy = stream.ConsumeIntegral<double>();
  }

  struct GeoPolygon* geo_polygon =
      static_cast<struct GeoPolygon*>(malloc(sizeof(struct GeoPolygon)));
  geo_polygon->num_vertices = stream.ConsumeIntegral<size_t>();
  geo_polygon->vertices =
      static_cast<struct GeoVertex*>(malloc(sizeof(struct GeoVertex) *
                                            geo_polygon->num_vertices));
  for (size_t i = 0; i < geo_polygon->num_vertices; i++) {
    geo_polygon->vertices[i].x = stream.ConsumeIntegral<double>();
    geo_polygon->vertices[i].y = stream.ConsumeIntegral<double>();
  }

  cellBoundaryInsidePolygon(geo_polygon, bboxes, boundaries, boundary_bboxes);

  free(bboxes);
  free(boundaries);
  free(boundary_bboxes);
  free(geo_polygon->vertices);
  free(geo_polygon);

  return 0;
}