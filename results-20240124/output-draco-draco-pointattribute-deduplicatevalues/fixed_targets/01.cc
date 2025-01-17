 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/core/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  draco::PointAttribute point_attribute;
  draco::GeometryAttribute geometry_attribute;
  const int attribute_id = stream.ConsumeIntegral<int>();

  int ret = point_attribute.DeduplicateValues(&geometry_attribute, attribute_id);

  return ret;
}