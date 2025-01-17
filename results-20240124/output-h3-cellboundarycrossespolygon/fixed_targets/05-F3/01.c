#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "geoPolygon.h"
#include "geoBBox.h"
#include "cellBoundary.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct GeoPolygon geoPolygon;
  struct BBox bboxes;
  struct CellBoundary boundary;
  struct BBox boundaryBBox;
  memset(&geoPolygon, 0, sizeof(geoPolygon));
  memset(&bboxes, 0, sizeof(bboxes));
  memset(&boundary, 0, sizeof(boundary));
  memset(&boundaryBBox, 0, sizeof(boundaryBBox));

  geoPolygon.numPoints = stream.ConsumeIntegralInRange<uint32_t>(0, 100);
  geoPolygon.points =
      (struct GeoPoint*)malloc(sizeof(struct GeoPoint) * geoPolygon.numPoints);
  for (uint32_t i = 0; i < geoPolygon.numPoints; i++) {
    geoPolygon.points[i].x = stream.ConsumeIntegral<int32_t>();
    geoPolygon.points[i].y = stream.ConsumeIntegral<int32_t>();
  }

  bboxes.x1 = stream.ConsumeIntegral<int32_t>();
  bboxes.y1 = stream.ConsumeIntegral<int32_t>();
  bboxes.x2 = stream.ConsumeIntegral<int32_t>();
  bboxes.y2 = stream.ConsumeIntegral<int32_t>();

  boundary.x1 = stream.ConsumeIntegral<int32_t>();
  boundary.y1 = stream.ConsumeIntegral<int32_t>();
  boundary.x2 = stream.ConsumeIntegral<int32_t>();
  boundary.y2 = stream.ConsumeIntegral<int32_t>();

  boundaryBBox.x1 = stream.ConsumeIntegral<int32_t>();
  boundaryBBox.y1 = stream.ConsumeIntegral<int32_t>();
  boundaryBBox.x2 = stream.ConsumeIntegral<int32_t>();
  boundaryBBox.y2 = stream.ConsumeIntegral<int32_t>();

  cellBoundaryCrossesPolygon(&geoPolygon, &bboxes, &boundary, &boundaryBBox);

  free(geoPolygon.points);
  return 0;
}