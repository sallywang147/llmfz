#include <fuzzer/FuzzedDataProvider.h>
#include "h3api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for the function call
  GeoLoop geoloop;
  BBox loopBBox;
  CellBoundary boundary;
  BBox boundaryBBox;

  // Consume data for GeoLoop
  geoloop.numVerts = stream.ConsumeIntegralInRange<int>(0, 10);
  for (int i = 0; i < geoloop.numVerts; i++) {
    geoloop.verts[i].lat = stream.ConsumeFloatingPoint<double>();
    geoloop.verts[i].lon = stream.ConsumeFloatingPoint<double>();
  }

  // Consume data for loopBBox
  loopBBox.north = stream.ConsumeFloatingPoint<double>();
  loopBBox.south = stream.ConsumeFloatingPoint<double>();
  loopBBox.east = stream.ConsumeFloatingPoint<double>();
  loopBBox.west = stream.ConsumeFloatingPoint<double>();

  // Consume data for CellBoundary
  boundary.numVerts = stream.ConsumeIntegralInRange<int>(0, 10);
  for (int i = 0; i < boundary.numVerts; i++) {
    boundary.verts[i].lat = stream.ConsumeFloatingPoint<double>();
    boundary.verts[i].lon = stream.ConsumeFloatingPoint<double>();
  }

  // Consume data for boundaryBBox
  boundaryBBox.north = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.south = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.east = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.west = stream.ConsumeFloatingPoint<double>();

  // Call the function with the defined parameters
  cellBoundaryCrossesGeoLoop(&geoloop, &loopBBox, &boundary, &boundaryBBox);

  return 0;
}