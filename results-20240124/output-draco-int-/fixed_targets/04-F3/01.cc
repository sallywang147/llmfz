#include <fuzzer/FuzzedDataProvider.h>
#include <draco/src/draco/core/point_attribute.h>
#include <draco/src/draco/core/geometry_attribute.h>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::PointAttribute attribute;
  draco::GeometryAttribute geometry_attribute;
  draco::PointAttribute::DeduplicateTypedValues<unsigned int>(&attribute,
                                                           &geometry_attribute,
                                                           0);
  return 0;
}
}