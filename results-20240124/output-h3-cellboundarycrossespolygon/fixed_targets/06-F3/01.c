#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "cellboundary.h"
#include "geopolygon.h"
#include "geopoint.h"
#include "bbox.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const int num_points = provider.ConsumeIntegralInRange<int>(1, 100);
  std::vector<GeoPoint> points;
  for (int i = 0; i < num_points; i++) {
    points.push_back(GeoPoint(provider.ConsumeIntegral<double>(),
                               provider.ConsumeIntegral<double>()));
  }
  GeoPolygon geo_polygon(points);

  const int num_bboxes = provider.ConsumeIntegralInRange<int>(1, 100);
  std::vector<BBox> bboxes;
  for (int i = 0; i < num_bboxes; i++) {
    bboxes.push_back(BBox(provider.ConsumeIntegral<double>(),
                           provider.ConsumeIntegral<double>(),
                           provider.ConsumeIntegral<double>(),
                           provider.ConsumeIntegral<double>()));
  }

  CellBoundary boundary;
  BBox boundary_bbox;
  cellBoundaryCrossesPolygon(&geo_polygon, bboxes.data(), &boundary,
                             &boundary_bbox);

  return 0;
}