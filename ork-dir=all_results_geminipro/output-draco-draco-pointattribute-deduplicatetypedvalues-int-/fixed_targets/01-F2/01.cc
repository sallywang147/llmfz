#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  const int num_values = stream.ConsumeIntegral<int32_t>();
  draco::PointAttribute::DeduplicateTypedValues<int32_t>(&point_attribute,
                                                    &geometry_attribute,
                                                    num_values);
  return 0;
}