#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cellBoundaryInsidePolygon.h"

extern "C" {
#include "cellBoundaryInsidePolygon.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  // Generate a random GeoPolygon.
  struct GeoPolygon geoPolygon;
  geoPolygon.numPoints = fdp.ConsumeIntegralInRange<uint32_t>(0, 100);
  geoPolygon.points =
      (struct GeoPoint *)malloc(sizeof(struct GeoPoint) * geoPolygon.numPoints);
  for (uint32_t i = 0; i < geoPolygon.numPoints; i++) {
    geoPolygon.points[i].lat = fdp.ConsumeFloat();
    geoPolygon.points[i].lon = fdp.ConsumeFloat();
  }

  // Generate a random BBox.
  struct BBox bbox;
  bbox.minLat = fdp.ConsumeFloat();
  bbox.minLon = fdp.ConsumeFloat();
  bbox.maxLat = fdp.ConsumeFloat();
  bbox.maxLon = fdp.ConsumeFloat();

  // Generate a random CellBoundary.
  struct CellBoundary boundary;
  boundary.numPoints = fdp.ConsumeIntegralInRange<uint32_t>(0, 100);
  boundary.points =
      (struct GeoPoint *)malloc(sizeof(struct GeoPoint) * boundary.numPoints);
  for (uint32_t i = 0; i < boundary.numPoints; i++) {
    boundary.points[i].lat = fdp.ConsumeFloat();
    boundary.points[i].lon = fdp.ConsumeFloat();
  }

  // Generate a random BBox for the CellBoundary.
  struct BBox boundaryBBox;
  boundaryBBox.minLat = fdp.ConsumeFloat();
  boundaryBBox.minLon = fdp.ConsumeFloat();
  boundaryBBox.maxLat = fdp.ConsumeFloat();
  boundaryBBox.maxLon = fdp.ConsumeFloat();

  // Call the function under test.
  bool result = cellBoundaryInsidePolygon(&geoPolygon, &bbox, &boundary,
                                          &boundaryBBox);

  // Free the allocated memory.
  free(geoPolygon.points);
  free(boundary.points);

  return 0;
}