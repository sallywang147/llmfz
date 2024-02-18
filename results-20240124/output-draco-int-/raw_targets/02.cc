 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/point_cloud/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute point_attribute(&geometry_attribute);
  draco::PointAttribute::DeduplicateTypedValues<unsigned int>(&point_attribute,
                                                               &geometry_attribute,
                                                               0);
  return 0;
}