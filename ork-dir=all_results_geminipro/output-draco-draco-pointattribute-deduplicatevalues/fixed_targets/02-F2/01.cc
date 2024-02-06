#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "draco/src/draco/attributes/point_attribute.h"
#include "draco/src/draco/core/geometry_attribute.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute point_attribute;

  FuzzedDataProvider provider(data, size);
  const int num_points = provider.ConsumeIntegral<int>();
  draco::PointAttribute::DeduplicateValues(
      &point_attribute, &geometry_attribute, num_points);

  return 0;
}