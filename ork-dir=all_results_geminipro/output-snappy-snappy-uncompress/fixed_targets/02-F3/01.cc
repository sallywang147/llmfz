#include <stddef.h>
#include <stdint.h>

#include <cassert>
#include <string>

#include "snappy.h"

extern "C" {
#include "zlib.h"
}

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

  // Variable only used in debug builds.
  (void)uncompress_succeeded;
  assert(uncompress_succeeded);

  return 0;
}