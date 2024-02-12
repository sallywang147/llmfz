 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/core/geometry_attribute.h"
#include "draco/src/draco/point_cloud/point_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::GeometryAttribute geometry_attribute;
  geometry_attribute.Init(draco::GeometryAttribute::POSITION,
                          draco::DataType::DT_FLOAT32,
                          draco::DataType::DT_FLOAT32, 3, 3);

  draco::PointAttribute point_attribute;
  point_attribute.Init(draco::PointAttribute::POSITION, geometry_attribute,
                      draco::PointAttribute::VALUE_PER_VERTEX);
  point_attribute.DeduplicateValues(&point_attribute, &geometry_attribute, 3);

  return 0;
}