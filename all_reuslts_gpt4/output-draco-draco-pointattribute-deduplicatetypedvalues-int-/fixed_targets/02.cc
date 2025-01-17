#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/point_cloud/point_attribute.h"
#include "draco/src/draco/attributes/geometry_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  draco::GeometryAttribute::Type attribute_type = static_cast<draco::GeometryAttribute::Type>(stream.ConsumeIntegralInRange<int>(0, draco::GeometryAttribute::Type::INVALID));
  draco::GeometryAttribute geometry_attribute;
  geometry_attribute.Init(attribute_type, nullptr, 3, draco::DT_INT32, false, 12, 0);

  draco::PointAttribute point_attribute;
  point_attribute.Init(attribute_type, nullptr, 3, draco::DT_INT32, false, 12, 0);

  int num_values = stream.ConsumeIntegral<int>();
  point_attribute.DeduplicateTypedValues<int>(&geometry_attribute, num_values);

  return 0;
}