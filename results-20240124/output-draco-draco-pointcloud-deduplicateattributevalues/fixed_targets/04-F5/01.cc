#include <draco/core/draco_encoder_options.h>
#include <draco/core/draco_types.h>
#include <draco/mesh/mesh.h>

#include <draco/point_cloud/point_cloud.h>

extern "C" {
#include <draco/mesh/mesh_encoder.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud point_cloud;
  point_cloud.DeduplicateAttributeValues();
  point_cloud.DeduplicatePointIds();
  return 0;
}