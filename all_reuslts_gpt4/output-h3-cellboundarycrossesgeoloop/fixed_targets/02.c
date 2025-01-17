#include <fuzzer/FuzzedDataProvider.h>
#include "h3api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for the function
  GeoLoop geoloop;
  BBox loopBBox;
  CellBoundary boundary;
  BBox boundaryBBox;

  // Consume data for GeoLoop
  for (int i = 0; i < stream.ConsumeIntegralInRange(0, MAX_CELL_BNDRY_VERTS); i++) {
    geoloop.loop[i].lat = stream.ConsumeFloatingPointInRange(-M_PI, M_PI);
    geoloop.loop[i].lon = stream.ConsumeFloatingPointInRange(-2 * M_PI, 2 * M_PI);
  }
  geoloop.numVerts = stream.ConsumeIntegralInRange(0, MAX_CELL_BNDRY_VERTS);

  // Consume data for BBox
  loopBBox.north = stream.ConsumeFloatingPointInRange(-M_PI, M_PI);
  loopBBox.south = stream.ConsumeFloatingPointInRange(-M_PI, M_PI);
  loopBBox.east = stream.ConsumeFloatingPointInRange(-2 * M_PI, 2 * M_PI);
  loopBBox.west = stream.ConsumeFloatingPointInRange(-2 * M_PI, 2 * M_PI);

  // Consume data for CellBoundary
  for (int i = 0; i < stream.ConsumeIntegralInRange(0, MAX_CELL_BNDRY_VERTS); i++) {
    boundary.verts[i].lat = stream.ConsumeFloatingPointInRange(-M_PI, M_PI);
    boundary.verts[i].lon = stream.ConsumeFloatingPointInRange(-2 * M_PI, 2 * M_PI);
  }
  boundary.numVerts = stream.ConsumeIntegralInRange(0, MAX_CELL_BNDRY_VERTS);

  // Consume data for BBox
  boundaryBBox.north = stream.ConsumeFloatingPointInRange(-M_PI, M_PI);
  boundaryBBox.south = stream.ConsumeFloatingPointInRange(-M_PI, M_PI);
  boundaryBBox.east = stream.ConsumeFloatingPointInRange(-2 * M_PI, 2 * M_PI);
  boundaryBBox.west = stream.ConsumeFloatingPointInRange(-2 * M_PI, 2 * M_PI);

  // Call the function with the initialized parameters
  cellBoundaryCrossesGeoLoop(&geoloop, &loopBBox, &boundary, &boundaryBBox);

  return 0;
}