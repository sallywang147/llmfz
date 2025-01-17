 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud point_cloud;
  draco::PointCloud::Attribute attribute;
  attribute.Init(draco::GeometryAttribute::POSITION, draco::DataType::DT_INT32, 3,
                  false, false, 0);
  point_cloud.AddAttribute(attribute, false);

  point_cloud.DeduplicateAttributeValues(&point_cloud);

  return 0;
}