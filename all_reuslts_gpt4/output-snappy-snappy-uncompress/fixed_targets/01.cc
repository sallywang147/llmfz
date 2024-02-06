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
  snappy::StringSink compressed_sink(&compressed);
  snappy::UncheckedByteArraySink unchecked_compressed_sink(compressed.data());

  snappy::Compress(input.data(), input.size(), &compressed_sink);

  std::string uncompressed_after_compress;
  snappy::StringSink uncompressed_sink(&uncompressed_after_compress);

  bool uncompress_succeeded = snappy::Uncompress(&unchecked_compressed_sink, &uncompressed_sink);

  (void)uncompress_succeeded; // Variable only used in debug builds.
  assert(uncompress_succeeded);
  assert(input == uncompressed_after_compress);
  return 0;
}