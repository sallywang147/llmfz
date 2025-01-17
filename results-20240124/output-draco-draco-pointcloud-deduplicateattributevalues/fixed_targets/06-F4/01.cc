#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "draco/compression/decode.h"
#include "draco/core/decoder_buffer.h"
#include "draco/core/draco_types.h"
#include "draco/core/geometry.h"
#include "draco/core/point_cloud.h"
#include "draco/core/status.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  draco::DecoderBuffer buffer;
  if (!buffer.Init(data, size)) {
    return 0;
  }
  draco::Decoder decoder;
  draco::PointCloud point_cloud;
  auto status = decoder.DecodePointCloudFromBuffer(&buffer, &point_cloud);
  if (!status.ok()) {
    return 0;
  }
  point_cloud.DeduplicateAttributeValues(&point_cloud);
  return 0;
}