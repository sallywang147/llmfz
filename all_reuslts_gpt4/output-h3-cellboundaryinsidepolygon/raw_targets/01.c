#include <fuzzer/FuzzedDataProvider.h>
#include "h3api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the GeoPolygon
  GeoPolygon geoPolygon;
  geoPolygon.geofence.numVerts = stream.ConsumeIntegralInRange<size_t>(0, 10);
  geoPolygon.geofence.verts = new GeoCoord[geoPolygon.geofence.numVerts];
  for (size_t i = 0; i < geoPolygon.geofence.numVerts; ++i) {
    geoPolygon.geofence.verts[i].lat = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
    geoPolygon.geofence.verts[i].lon = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
  }
  geoPolygon.numHoles = 0;
  geoPolygon.holes = nullptr;

  // Initialize the BBox
  BBox bboxes;
  bboxes.north = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
  bboxes.south = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
  bboxes.east = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
  bboxes.west = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
  bboxes.southWest = {bboxes.south, bboxes.west};
  bboxes.northEast = {bboxes.north, bboxes.east};

  // Initialize the CellBoundary
  CellBoundary boundary;
  boundary.numVerts = stream.ConsumeIntegralInRange<size_t>(0, 10);
  boundary.verts = new GeoCoord[boundary.numVerts];
  for (size_t i = 0; i < boundary.numVerts; ++i) {
    boundary.verts[i].lat = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
    boundary.verts[i].lon = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
  }

  // Initialize the boundaryBBox
  BBox boundaryBBox;
  boundaryBBox.north = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
  boundaryBBox.south = stream.ConsumeFloatingPointInRange<double>(-90.0, 90.0);
  boundaryBBox.east = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
  boundaryBBox.west = stream.ConsumeFloatingPointInRange<double>(-180.0, 180.0);
  boundaryBBox.southWest = {boundaryBBox.south, boundaryBBox.west};
  boundaryBBox.northEast = {boundaryBBox.north, boundaryBBox.east};

  // Call the function to be fuzzed
  cellBoundaryInsidePolygon(&geoPolygon, &bboxes, &boundary, &boundaryBBox);

  // Clean up
  delete[] geoPolygon.geofence.verts;
  delete[] boundary.verts;

  return 0;
}