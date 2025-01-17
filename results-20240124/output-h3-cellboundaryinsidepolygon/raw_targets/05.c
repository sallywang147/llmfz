 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "GeoPolygon.h"
#include "GeoPolygon.cpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int num_points = stream.ConsumeIntegral<int>();
  const int num_bboxes = stream.ConsumeIntegral<int>();
  const int num_boundaries = stream.ConsumeIntegral<int>();
  struct GeoPolygon *geoPolygon = createGeoPolygon(num_points);
  struct BBox *bboxes_array = createBBoxArray(num_bboxes);
  struct CellBoundary *boundary = createCellBoundary();
  struct BBox *boundaryBBox = createBBox();

  for (int i = 0; i < num_points; i++) {
    const double x = stream.ConsumeFloatingPoint<double>();
    const double y = stream.ConsumeFloatingPoint<double>();
    addPoint(geoPolygon, x, y);
  }

  for (int i = 0; i < num_bboxes; i++) {
    const double x1 = stream.ConsumeFloatingPoint<double>();
    const double y1 = stream.ConsumeFloatingPoint<double>();
    const double x2 = stream.ConsumeFloatingPoint<double>();
    const double y2 = stream.ConsumeFloatingPoint<double>();
    addBBox(bboxes_array, x1, y1, x2, y2);
  }

  for (int i = 0; i < num_boundaries; i++) {
    const double x1 = stream.ConsumeFloatingPoint<double>();
    const double y1 = stream.ConsumeFloatingPoint<double>();
    const double x2 = stream.ConsumeFloatingPoint<double>();
    const double y2 = stream.ConsumeFloatingPoint<double>();
    addBoundary(boundary, x1, y1, x2, y2);
  }

  cellBoundaryInsidePolygon(geoPolygon, bboxes_array, boundary, boundaryBBox);

  destroyGeoPolygon(geoPolygon);
  destroyBBoxArray(bboxes_array);
  destroyCellBoundary(boundary);
  destroyBBox(boundaryBBox);
  return 0;
}