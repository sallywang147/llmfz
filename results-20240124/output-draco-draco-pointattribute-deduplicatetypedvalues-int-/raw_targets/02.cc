 #include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/compression/decode.h"
#include "draco/src/draco/core/decoder_buffer.h"
#include "draco/src/draco/point_cloud/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::DecoderBuffer buffer;
  buffer.Init(reinterpret_cast<const char *>(data), size);

  draco::Decoder decoder;
  decoder.SetSkipAttributeTransform(draco::GeometryAttribute::POSITION);
  decoder.DecodePointCloudFromBuffer(&buffer);

  draco::PointAttribute* attribute = new draco::PointAttribute;
  draco::GeometryAttribute* geometry_attribute = new draco::GeometryAttribute;
  int value = 0;
  draco::PointAttribute::DeduplicateTypedValues<int>(attribute, geometry_attribute, value);

  return 0;
}