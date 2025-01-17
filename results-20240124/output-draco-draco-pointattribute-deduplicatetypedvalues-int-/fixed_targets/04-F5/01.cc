#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/point_cloud/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute point_attribute;

  FuzzedDataProvider stream(data, size);
  int num_points = stream.ConsumeIntegralInRange<int>(0, 10000);
  for (int i = 0; i < num_points; i++) {
    point_attribute.AddValue(stream.ConsumeIntegral<int>());
  }

  // Call the DeduplicateTypedValues function
  point_attribute.DeduplicateTypedValues<int>(&point_attribute, &geometry_attribute,
                                         num_points);

  return 0;
}