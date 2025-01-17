 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "freetype/ft2build.h"
#include FT_FREETYPE_H
#include FT_CACHE_H
#include FT_CACHE_IMAGE_H
#include FT_CACHE_SMALL_BITMAPS_H
#include FT_SYNTHESIS_H
#include FT_ADVANCES_H
#include FT_OUTLINE_H
#include FT_BBOX_H
#include FT_MODULE_H
#include FT_DRIVER_H
#include FT_MULTIPLE_MASTERS_H

#include "freetype/gzip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_size = stream.ConsumeIntegralInRange<size_t>(1, 1024 * 1024);
  std::vector<uint8_t> compressed_data = stream.ConsumeBytes<uint8_t>(max_size);
  std::vector<uint8_t> uncompressed_data;
  if (freetype::GzipFuzzTarget::GzipFuzzTarget(compressed_data.data(),
                                               compressed_data.size(),
                                               &uncompressed_data)) {
    return 0;
  }
  return 0;
}