#include <fuzzer/FuzzedDataProvider.h>

#include "draco/src/draco/compression/decode.h"
#include "draco/src/draco/core/decoder_buffer.h"
#include "draco/src/draco/point_cloud/point_cloud.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::DecoderBuffer buffer;
  buffer.Init(reinterpret_cast<const char *>(data), size);

  draco::Decoder decoder;
  auto point_cloud_or = decoder.DecodePointCloudFromBuffer(&buffer);
  if (!point_cloud_or.ok()) {
    return 0;
  }

  std::unique_ptr<draco::PointCloud> point_cloud(point_cloud_or.value().release());
  if (!point_cloud) {
    return 0;
  }

  point_cloud->DeduplicateAttributeValues(point_cloud.get());

  return 0;
}