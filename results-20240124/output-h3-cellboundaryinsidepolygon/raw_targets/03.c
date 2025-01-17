 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "cellBoundary.h"
#include "geoPolygon.h"
#include "geoPolygonInternal.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct GeoPolygon geoPolygon;
  geoPolygon.numPoints = stream.ConsumeIntegral<uint32_t>();
  geoPolygon.points = new double[geoPolygon.numPoints * 2];
  for (uint32_t i = 0; i < geoPolygon.numPoints; i++) {
    geoPolygon.points[2 * i] = stream.ConsumeFloatingPoint<double>();
    geoPolygon.points[2 * i + 1] = stream.ConsumeFloatingPoint<double>();
  }

  struct BBox bboxes;
  bboxes.minLon = stream.ConsumeFloatingPoint<double>();
  bboxes.maxLon = stream.ConsumeFloatingPoint<double>();
  bboxes.minLat = stream.ConsumeFloatingPoint<double>();
  bboxes.maxLat = stream.ConsumeFloatingPoint<double>();

  struct CellBoundary boundary;
  boundary.numPoints = stream.ConsumeIntegral<uint32_t>();
  boundary.points = new double[boundary.numPoints * 2];
  for (uint32_t i = 0; i < boundary.numPoints; i++) {
    boundary.points[2 * i] = stream.ConsumeFloatingPoint<double>();
    boundary.points[2 * i + 1] = stream.ConsumeFloatingPoint<double>();
  }

  struct BBox boundaryBBox;
  boundaryBBox.minLon = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.maxLon = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.minLat = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.maxLat = stream.ConsumeFloatingPoint<double>();

  cellBoundaryInsidePolygon(&geoPolygon, &bboxes, &boundary, &boundaryBBox);

  delete[] geoPolygon.points;
  delete[] boundary.points;
  return 0;
}