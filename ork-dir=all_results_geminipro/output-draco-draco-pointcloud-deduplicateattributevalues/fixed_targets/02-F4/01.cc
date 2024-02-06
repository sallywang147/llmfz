#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "draco/src/draco/core/point_cloud.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud pc;
  pc.DecodeFromBuffer(data, size);  // Decode the point cloud from the input buffer
  bool result = pc.DeduplicateAttributeValues();  // Remove the pointer to `pc`
  return 0;
}