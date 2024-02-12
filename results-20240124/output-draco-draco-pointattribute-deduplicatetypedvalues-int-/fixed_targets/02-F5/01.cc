#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/compression/decode.h"
#include "draco/src/draco/core/decoder_buffer.h"
#include "draco/src/draco/point_cloud/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::DecoderBuffer buffer;
  buffer.Init(reinterpret_cast<const char *>(data), size);

  draco::Decoder decoder;
  decoder.SetSkipAttributeTransform(draco::GeometryAttribute::POSITION);
  draco::PointCloud point_cloud;
  decoder.DecodePointCloudFromBuffer(&buffer, &point_cloud);

  draco::PointAttribute attribute;
  draco::GeometryAttribute geometry_attribute;
  int value = 0;
  draco::PointAttribute::DeduplicateTypedValues<int>(&attribute, &geometry_attribute, value);

  // Call the target function.
  draco::PointAttribute::DeduplicateTypedValues<int>(&attribute, &geometry_attribute, value);

  return 0;
}