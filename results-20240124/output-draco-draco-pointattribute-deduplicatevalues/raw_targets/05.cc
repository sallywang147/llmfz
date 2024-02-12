 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/point_cloud/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  FuzzedDataProvider stream(data, size);
  int num_points = stream.ConsumeIntegral<int>();
  draco::PointAttribute::DeduplicateValues(&point_attribute, &geometry_attribute,
                                          num_points);
  return 0;
}