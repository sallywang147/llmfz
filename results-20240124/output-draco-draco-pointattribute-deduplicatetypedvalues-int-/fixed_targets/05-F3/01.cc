#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/point_attribute.h"
#include "draco/src/draco/point_cloud/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud point_cloud;
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute::DeduplicateTypedValues<int>(&point_attribute,
                                                    &geometry_attribute, 0);
  draco::PointAttribute::DeduplicateTypedValues<int>(&point_attribute,
                                                    &geometry_attribute, 0);
  return 0;
}