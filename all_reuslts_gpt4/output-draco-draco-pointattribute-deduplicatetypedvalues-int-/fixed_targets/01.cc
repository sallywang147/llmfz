#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/attributes/point_attribute.h"
#include "draco/src/draco/attributes/geometry_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  int num_values = stream.ConsumeIntegral<int>();

  draco::GeometryAttribute geom_attr;
  draco::PointAttribute point_attr(&geom_attr);

  point_attr.DeduplicateTypedValues<int>(&point_attr, &geom_attr, num_values);

  return 0;
}