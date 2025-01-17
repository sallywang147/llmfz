#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/draco_types.h"
#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::FuzzedDataProvider fuzzed_data_provider(data, size);
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute::DeduplicateTypedValues<int>(&point_attribute,
                                                     &geometry_attribute, 0);

  return 0;
}