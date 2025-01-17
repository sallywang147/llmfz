#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cellBoundary.h"
#include "geoPolygon.h"
#include "geoPolygon_internal.h"

extern "C" {
#include "cellBoundary.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t num_bboxes = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<BBox> bboxes;
  for (size_t i = 0; i < num_bboxes; i++) {
    bboxes.push_back(provider.ConsumeBytes<BBox>(sizeof(BBox)));
  }
  const size_t num_boundaries = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<CellBoundary> boundaries;
  for (size_t i = 0; i < num_boundaries; i++) {
    boundaries.push_back(provider.ConsumeBytes<CellBoundary>(sizeof(CellBoundary)));
  }
  const size_t num_boundary_bboxes = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<BBox> boundary_bboxes;
  for (size_t i = 0; i < num_boundary_bboxes; i++) {
    boundary_bboxes.push_back(provider.ConsumeBytes<BBox>(sizeof(BBox)));
  }
  GeoPolygon geoPolygon;
  geoPolygon.num_vertices = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  geoPolygon.vertices = new GeoVertex[geoPolygon.num_vertices];
  for (size_t i = 0; i < geoPolygon.num_vertices; i++) {
    geoPolygon.vertices[i] = provider.ConsumeBytes<GeoVertex>(sizeof(GeoVertex));
  }
  cellBoundaryCrossesPolygon(&geoPolygon, bboxes.data(), boundaries.data(), boundary_bboxes.data());
  delete[] geoPolygon.vertices;
  return 0;
}