#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  draco::PointAttribute attribute;
  draco::GeometryAttribute geometry_attribute;
  int value_to_remove = provider.ConsumeIntegral<int>();
  attribute.DeduplicateValues(&geometry_attribute, value_to_remove);
  return 0;
}