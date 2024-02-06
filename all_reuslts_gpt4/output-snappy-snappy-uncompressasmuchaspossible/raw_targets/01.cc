#include <stddef.h>
#include <stdint.h>

#include <cassert>
#include <string>

#include "snappy.h"
#include "snappy-sinksource.h"

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);

  std::string compressed;
  size_t compressed_size = snappy::Compress(input.data(), input.size(), &compressed);

  (void)compressed_size; // Variable only used in debug builds.
  assert(compressed_size == compressed.size());
  assert(compressed.size() <= snappy::MaxCompressedLength(input.size()));
  assert(snappy::IsValidCompressedBuffer(compressed.data(), compressed.size()));

  snappy::UncheckedByteArraySink compressed_sink(&compressed);
  std::string uncompressed_after_compress;
  snappy::UncheckedByteArraySink uncompressed_sink(&uncompressed_after_compress);

  size_t result = snappy::UncompressAsMuchAsPossible(&compressed_sink, &uncompressed_sink);

  (void)result; // Variable only used in debug builds.
  assert(result <= input.size());

  return 0;
}