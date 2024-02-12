#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"
#include "draco/src/draco/core/status.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  FuzzedDataProvider provider(data, size);
  int num_points = provider.ConsumeIntegral<int>();
  return point_attribute.DeduplicateTypedValues<int>(&geometry_attribute,
                                                  &geometry_attribute, num_points);
}