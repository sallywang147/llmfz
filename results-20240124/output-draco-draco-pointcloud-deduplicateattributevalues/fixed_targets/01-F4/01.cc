#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "draco/src/draco/core/point_cloud.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud point_cloud;
  draco::PointCloud::Attribute attribute;
  attribute.attribute_type = draco::GeometryAttribute::POSITION;
  attribute.num_components = 3;
  attribute.normalized = false;
  attribute.byte_stride = 0;
  attribute.byte_offset = 0;
  attribute.unique_id = 0;
  point_cloud.AddAttribute(attribute);

  point_cloud.DeduplicateAttributeValues();

  return 0;
}