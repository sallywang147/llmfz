#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  draco::PointAttribute attribute;
  draco::GeometryAttribute geometry_attribute;
  int num_points = provider.ConsumeIntegral<int>();
  return attribute.DeduplicateTypedValues<unsigned int>(&geometry_attribute,
                                                     &geometry_attribute,
                                                     num_points);
}
}