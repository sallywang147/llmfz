 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/point_cloud/point_attribute.h"
#include "draco/src/draco/point_cloud/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud pc;
  draco::PointAttribute attribute;
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute::DeduplicateValues(&attribute, &geometry_attribute, 0);
  return 0;
}