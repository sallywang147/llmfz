#include <stddef.h>
#include <stdint.h>

#include <cassert>
#include <string>

#include "snappy.h"

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);

  std::string compressed;
  size_t compressed_size = snappy::Compress(input.data(), input.size(), &compressed);

  (void)compressed_size; // Variable only used in debug builds.
  assert(compressed_size == compressed.size());
  assert(compressed.size() <= snappy::MaxCompressedLength(input.size()));
  assert(snappy::IsValidCompressedBuffer(compressed.data(), compressed.size()));

  std::string uncompressed;
  size_t uncompressed_size = snappy::UncompressAsMuchAsPossible(
      snappy::MakeStringSink(&compressed), snappy::MakeStringSink(&uncompressed));

  (void)uncompressed_size; // Variable only used in debug builds.
  assert(uncompressed_size <= input.size());
  assert(uncompressed.size() == uncompressed_size);
  return 0;
}