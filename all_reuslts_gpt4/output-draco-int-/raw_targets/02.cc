#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/attributes/point_attribute.h"
#include "draco/src/draco/attributes/geometry_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a PointAttribute.
  draco::PointAttribute point_attribute;

  // Create a GeometryAttribute.
  draco::GeometryAttribute geometry_attribute;

  // Consume an integer from the data stream.
  int num_values = stream.ConsumeIntegral<int>();

  // Call the function to fuzz.
  point_attribute.DeduplicateTypedValues<unsigned int>(&geometry_attribute, num_values);

  return 0;
}