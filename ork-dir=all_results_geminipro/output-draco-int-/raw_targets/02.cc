#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  int num_values = provider.ConsumeIntegralInRange<int>(0, 10000);
  int result = point_attribute.DeduplicateTypedValues<unsigned int>(
      &geometry_attribute, num_values);
  return result;
}