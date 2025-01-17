#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/point_cloud.h"

extern "C" {
#include "draco/src/draco/core/draco_types.h"
#include "draco/src/draco/core/point_attribute.h"
#include "draco/src/draco/core/point_cloud.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud point_cloud;
  point_cloud.DeduplicatePointIds();  // Fix the function name
  return 0;
}