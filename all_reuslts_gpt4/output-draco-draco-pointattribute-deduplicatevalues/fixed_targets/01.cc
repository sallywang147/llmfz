#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/attributes/geometry_attribute.h"
#include "draco/src/draco/attributes/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a PointAttribute.
  draco::PointAttribute point_attribute;
  point_attribute.Init(draco::GeometryAttribute::POSITION, nullptr, 3, draco::DT_FLOAT32, false, 12, 0);

  // Create a GeometryAttribute.
  draco::GeometryAttribute geometry_attribute;
  geometry_attribute.Init(draco::GeometryAttribute::POSITION, nullptr, 3, draco::DT_FLOAT32, false, 12, 0);

  // Get an integer from the data.
  int int_arg = stream.ConsumeIntegral<int>();

  // Call the function to fuzz.
  point_attribute.DeduplicateValues(&point_attribute, &geometry_attribute, int_arg);

  return 0;
}