#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/attributes/point_attribute.h"
#include "draco/src/draco/attributes/geometry_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int))
    return 0;

  FuzzedDataProvider stream(data, size);

  draco::GeometryAttribute::Type type = stream.PickValueInArray({draco::GeometryAttribute::POSITION,
                                                                 draco::GeometryAttribute::NORMAL,
                                                                 draco::GeometryAttribute::COLOR,
                                                                 draco::GeometryAttribute::TEX_COORD,
                                                                 draco::GeometryAttribute::GENERIC});
  draco::GeometryAttribute ga;
  ga.Init(type, nullptr, 3, draco::DT_FLOAT32, false, 12, 0);

  draco::PointAttribute pa;
  pa.Init(type, nullptr, 3, draco::DT_FLOAT32, false, 12, 0);

  int num_points = stream.ConsumeIntegral<int>();

  pa.DeduplicateValues(&pa, &ga, num_points);

  return 0;
}