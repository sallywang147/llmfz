 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/point_cloud/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  draco::PointAttribute attribute;
  draco::GeometryAttribute geometry_attribute;
  int num_points = stream.ConsumeIntegral<int>();
  int unsigned int draco::PointAttribute::DeduplicateTypedValues<unsigned int>(
      &attribute, &geometry_attribute, num_points);
  return 0;
}