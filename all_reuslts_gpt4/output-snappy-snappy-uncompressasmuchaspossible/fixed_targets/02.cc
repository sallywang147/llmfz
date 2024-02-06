#include <stddef.h>
#include <stdint.h>

#include <cassert>
#include <string>

#include "snappy.h"
#include "snappy-sinksource.h"
#include "fuzzer/FuzzedDataProvider.h"

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input = stream.ConsumeRemainingBytesAsString();

  snappy::Source* source = new snappy::StringSource(input);
  snappy::Sink* sink = new snappy::StringSink();

  snappy::Compress(source, sink);

  std::string compressed = static_cast<snappy::StringSink*>(sink)->contents();

  snappy::Source* compressed_source = new snappy::StringSource(compressed);
  snappy::Sink* uncompressed_sink = new snappy::StringSink();

  snappy::UncompressAsMuchAsPossible(compressed_source, uncompressed_sink);

  delete source;
  delete sink;
  delete compressed_source;
  delete uncompressed_sink;

  return 0;
}