#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

#include "GeoPolygon.h"
#include "BBox.h"
#include "CellBoundary.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<double> polygon_vertices;
  while (stream.remaining_bytes() > 1) {
    polygon_vertices.push_back(stream.ConsumeFloatingPoint<double>());
  }
  GeoPolygon geoPolygon(polygon_vertices);

  BBox bboxes[2];
  for (int i = 0; i < 2; i++) {
    bboxes[i].min_x = stream.ConsumeFloatingPoint<double>();
    bboxes[i].min_y = stream.ConsumeFloatingPoint<double>();
    bboxes[i].max_x = stream.ConsumeFloatingPoint<double>();
    bboxes[i].max_y = stream.ConsumeFloatingPoint<double>();
  }

  CellBoundary boundary;
  boundary.min_x = stream.ConsumeFloatingPoint<double>();
  boundary.min_y = stream.ConsumeFloatingPoint<double>();
  boundary.max_x = stream.ConsumeFloatingPoint<double>();
  boundary.max_y = stream.ConsumeFloatingPoint<double>();

  BBox boundaryBBox;
  boundaryBBox.min_x = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.min_y = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.max_x = stream.ConsumeFloatingPoint<double>();
  boundaryBBox.max_y = stream.ConsumeFloatingPoint<double>();

  cellBoundaryCrossesPolygon(&geoPolygon, bboxes, &boundary, &boundaryBBox);

  return 0;
}