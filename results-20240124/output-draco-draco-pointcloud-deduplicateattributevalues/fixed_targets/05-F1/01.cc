#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointCloud pc;
  pc.Decompress(data, size);
  pc.DeduplicateAttributeValues(&pc);

  return 0;
}