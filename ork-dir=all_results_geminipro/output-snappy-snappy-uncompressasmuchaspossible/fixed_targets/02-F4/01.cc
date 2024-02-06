#include <stddef.h>
#include <stdint.h>

#include <cassert>
#include <string>

#include "snappy.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::string input = fuzzed_data.ConsumeRemainingBytesAsString();

  std::string compressed;
  size_t compressed_size = snappy::Compress(input.data(), input.size(), &compressed);

  (void)compressed_size; // Variable only used in debug builds.
  assert(compressed_size == compressed.size());
  assert(compressed.size() <= snappy::MaxCompressedLength(input.size()));
  assert(snappy::IsValidCompressedBuffer(compressed.data(), compressed.size()));

  std::string uncompressed_after_compress;
  bool uncompress_succeeded = snappy::Uncompress(compressed.data(), compressed.size(), &uncompressed_after_compress);

  (void)uncompress_succeeded; // Variable only used in debug builds.
  assert(uncompress_succeeded);
  assert(input == uncompressed_after_compress);

  // Fuzz the UncompressAsMuchAsPossible function.
  std::string uncompressed_after_partial_uncompress;
  size_t uncompressed_size = snappy::UncompressAsMuchAsPossible(
      snappy::MakeStringSink(&compressed),
      snappy::MakeStringSink(&uncompressed_after_partial_uncompress));

  (void)uncompressed_size; // Variable only used in debug builds.
  assert(uncompressed_size <= input.size());
  assert(uncompressed_after_partial_uncompress.size() == uncompressed_size);
  assert(input.substr(0, uncompressed_size) == uncompressed_after_partial_uncompress);
  return 0;
}