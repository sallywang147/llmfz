 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "geoPolygon.h"
#include "bbox.h"
#include "cellBoundary.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct GeoPolygon geoPolygon;
  geoPolygon.numPoints = stream.ConsumeIntegral<uint8_t>();
  geoPolygon.points = new double[geoPolygon.numPoints * 2];
  for (uint8_t i = 0; i < geoPolygon.numPoints * 2; i++) {
    geoPolygon.points[i] = stream.ConsumeFloatingPoint<double>();
  }

  struct BBox bboxes[geoPolygon.numPoints];
  for (uint8_t i = 0; i < geoPolygon.numPoints; i++) {
    bboxes[i].xmin = stream.ConsumeFloatingPoint<double>();
    bboxes[i].ymin = stream.ConsumeFloatingPoint<double>();
    bboxes[i].xmax = stream.ConsumeFloatingPoint<double>();
    bboxes[i].ymax = stream.ConsumeFloatingPoint<double>();
  }

  struct CellBoundary boundary;
  boundary.numPoints = stream.ConsumeIntegral<uint8_t>();
  boundary.points = new double[boundary.numPoints * 2];
  for (uint8_t i = 0; i < boundary.numPoints * 2; i++) {
    boundary.points[i] = stream.ConsumeFloatingPoint<double>();
  }

  struct BBox boundaryBBox;
  boundaryBBox.xmin = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.ymin = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.xmax = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.ymax = stream.ConsumeFloatingPoint<double>();

  cellBoundaryInsidePolygon(&geoPolygon, bboxes, &boundary, &boundaryBBox);

  delete[] geoPolygon.points;
  delete[] boundary.points;

  return 0;
}