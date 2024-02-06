#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/point_cloud/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud point_cloud;
  
  // We need to add at least one attribute to the point cloud.
  draco::GeometryAttribute pos_att;
  pos_att.Init(draco::GeometryAttribute::POSITION,
               nullptr,  // No custom data.
               3,        // Number of components.
               draco::DT_FLOAT32,
               false,    // Not normalized.
               0,        // No stride.
               0);       // No byte offset.
  point_cloud.AddAttribute(pos_att, true, 0);  // No points.

  point_cloud.DeduplicateAttributeValues(&point_cloud);

  return 0;
}