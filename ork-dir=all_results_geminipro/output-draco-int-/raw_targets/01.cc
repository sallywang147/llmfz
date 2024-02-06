#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  draco::GeometryAttribute attribute;
  size_t num_points = provider.ConsumeIntegralInRange<size_t>(0, 100000);
  std::vector<uint32_t> values(num_points);
  for (size_t i = 0; i < num_points; i++) {
    values[i] = provider.ConsumeIntegral<uint32_t>();
  }
  attribute.Init(draco::GeometryAttribute::ValueType::UINT32, num_points,
                 values.data());
  draco::PointAttribute point_attribute;
  point_attribute.DeduplicateTypedValues<uint32_t>(&attribute, &attribute, 0);
  return 0;
}