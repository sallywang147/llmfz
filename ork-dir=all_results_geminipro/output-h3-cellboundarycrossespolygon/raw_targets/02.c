#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize GeoPolygon
  GeoPolygon geoPolygon;
  geoPolygon.numPoints = provider.ConsumeIntegralInRange<uint32_t>(0, 1000);
  geoPolygon.points = new GeoPoint[geoPolygon.numPoints];
  for (uint32_t i = 0; i < geoPolygon.numPoints; i++) {
    geoPolygon.points[i].x = provider.ConsumeIntegral<double>();
    geoPolygon.points[i].y = provider.ConsumeIntegral<double>();
  }

  // Initialize BBox
  BBox bboxes;
  bboxes.x0 = provider.ConsumeIntegral<double>();
  bboxes.y0 = provider.ConsumeIntegral<double>();
  bboxes.x1 = provider.ConsumeIntegral<double>();
  bboxes.y1 = provider.ConsumeIntegral<double>();

  // Initialize CellBoundary
  CellBoundary boundary;
  boundary.numPoints = provider.ConsumeIntegralInRange<uint32_t>(0, 1000);
  boundary.points = new GeoPoint[boundary.numPoints];
  for (uint32_t i = 0; i < boundary.numPoints; i++) {
    boundary.points[i].x = provider.ConsumeIntegral<double>();
    boundary.points[i].y = provider.ConsumeIntegral<double>();
  }

  // Initialize BBox boundaryBBox
  BBox boundaryBBox;
  boundaryBBox.x0 = provider.ConsumeIntegral<double>();
  boundaryBBox.y0 = provider.ConsumeIntegral<double>();
  boundaryBBox.x1 = provider.ConsumeIntegral<double>();
  boundaryBBox.y1 = provider.ConsumeIntegral<double>();

  // Call the function to be fuzzed
  bool result = cellBoundaryCrossesPolygon(&geoPolygon, &bboxes, &boundary, &boundaryBBox);

  // Cleanup
  delete[] geoPolygon.points;
  delete[] boundary.points;

  return 0;
}