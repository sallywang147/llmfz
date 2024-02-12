#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "draco/src/draco/compression/decode.h"
#include "draco/src/draco/core/decoder_buffer.h"
#include "draco/src/draco/point_cloud/point_cloud.h"
#include "draco/src/draco/point_cloud/point_cloud_builder.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::DecoderBuffer buffer;
  buffer.Init(reinterpret_cast<const char *>(data), size);

  draco::Decoder decoder;
  decoder.SetSkipAttributeTransform(draco::GeometryAttribute::POSITION);
  draco::PointCloud point_cloud;
  decoder.DecodePointCloudFromBuffer(&buffer, &point_cloud);

  point_cloud.DeduplicateAttributeValues(&point_cloud);

  return 0;
}