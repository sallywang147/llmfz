 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "cell_boundary.h"
#include "geo_polygon.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct GeoPolygon polygon;
  polygon.num_vertices = stream.ConsumeIntegral<uint32_t>();
  polygon.vertices =
      (struct GeoPoint*)malloc(polygon.num_vertices * sizeof(struct GeoPoint));
  for (uint32_t i = 0; i < polygon.num_vertices; i++) {
    polygon.vertices[i].lat = stream.ConsumeIntegral<double>();
    polygon.vertices[i].lon = stream.ConsumeIntegral<double>();
  }

  struct BBox bbox;
  bbox.min_lat = stream.ConsumeIntegral<double>();
  bbox.min_lon = stream.ConsumeIntegral<double>();
  bbox.max_lat = stream.ConsumeIntegral<double>();
  bbox.max_lon = stream.ConsumeIntegral<double>();

  struct CellBoundary boundary;
  boundary.lat = stream.ConsumeIntegral<double>();
  boundary.lon = stream.ConsumeIntegral<double>();
  boundary.bearing = stream.ConsumeIntegral<double>();

  struct BBox boundary_bbox;
  boundary_bbox.min_lat = stream.ConsumeIntegral<double>();
  boundary_bbox.min_lon = stream.ConsumeIntegral<double>();
  boundary_bbox.max_lat = stream.ConsumeIntegral<double>();
  boundary_bbox.max_lon = stream.ConsumeIntegral<double>();

  cellBoundaryCrossesPolygon(&polygon, &bbox, &boundary, &boundary_bbox);

  free(polygon.vertices);
  return 0;
}