 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/point_attribute.h"
#include "draco/src/draco/core/geometry_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  FuzzedDataProvider stream(data, size);
  int value = stream.ConsumeIntegral<int>();
  draco::PointAttribute::DeduplicateTypedValues<int>(&point_attribute,
                                                  &geometry_attribute, value);
  return 0;
}