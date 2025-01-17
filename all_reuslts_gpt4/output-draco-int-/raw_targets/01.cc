#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/attributes/point_attribute.h"
#include "draco/src/draco/attributes/geometry_attribute.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a PointAttribute and GeometryAttribute
  draco::PointAttribute pointAttribute;
  draco::GeometryAttribute geometryAttribute;

  // Consume data from the stream to set num_components and byte_stride for the attributes
  int num_components = stream.ConsumeIntegral<int>();
  int byte_stride = stream.ConsumeIntegral<int>();

  // Set the attributes
  geometryAttribute.Init(draco::GeometryAttribute::Type::POSITION,
                         nullptr, num_components, draco::DT_UINT32, false,
                         byte_stride, 0);
  pointAttribute.Init(geometryAttribute);

  // Consume remaining data from the stream to set the deduplication_id
  int deduplication_id = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  pointAttribute.DeduplicateTypedValues<unsigned int>(&pointAttribute, &geometryAttribute, deduplication_id);

  return 0;
}