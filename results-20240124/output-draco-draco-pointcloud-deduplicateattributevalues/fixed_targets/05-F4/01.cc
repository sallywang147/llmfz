#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "draco/src/draco/core/point_cloud.h"
#include "draco/src/draco/core/point_cloud/point_cloud.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud pc;
  if (!pc.Decompress(data, size)) {
    return 0;
  }
  pc.DeduplicateAttributeValues(&pc);

  return 0;
}