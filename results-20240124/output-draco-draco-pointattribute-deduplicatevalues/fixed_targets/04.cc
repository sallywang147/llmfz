 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/point_cloud/point_attribute.h"
#include "draco/src/draco/point_cloud/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointAttribute attribute;
  draco::GeometryAttribute geometry_attribute;
  draco::PointCloud point_cloud;
  attribute.DeduplicateValues(&geometry_attribute, &point_cloud, 0);
  return 0;
}