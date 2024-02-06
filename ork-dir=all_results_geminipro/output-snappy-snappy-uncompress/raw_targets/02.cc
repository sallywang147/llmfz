#include <stddef.h>
#include <stdint.h>

#include <cassert>
#include <string>

#include "snappy.h"

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Construct a Sink that writes to a string.
  std::string compressed;
  snappy::StringSink compressed_sink(&compressed);

  // Construct a Sink that writes to a string.
  std::string uncompressed;
  snappy::StringSink uncompressed_sink(&uncompressed);

  // Write the input data to the compressed Sink.
  compressed_sink.Append(reinterpret_cast<const char *>(data), size);

  // Uncompress the data from the compressed Sink to the uncompressed Sink.
  bool uncompress_succeeded = snappy::Uncompress(&compressed_sink, &uncompressed_sink);

  (void)uncompress_succeeded; // Variable only used in debug builds.
  assert(uncompress_succeeded);

  return 0;
}