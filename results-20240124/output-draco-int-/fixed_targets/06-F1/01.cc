#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute point_attribute;
  const int attribute_id = stream.ConsumeIntegral<int>();
  draco::PointAttribute::DeduplicateTypedValues<unsigned int>(
      &point_attribute, &geometry_attribute, attribute_id);
  return 0;
}