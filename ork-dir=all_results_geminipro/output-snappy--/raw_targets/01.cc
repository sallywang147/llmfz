#include <stddef.h>
#include <stdint.h>

#include <cassert>
#include <string>
#include <vector>

#include "snappy.h"

// Entry point for LibFuzzer.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);

  snappy::SnappyScatteredWriter writer;
  snappy::SnappyDecompressor decompressor;
  bool uncompress_succeeded = snappy::InternalUncompressAllTags<
      snappy::SnappyScatteredWriter<snappy::SnappySinkAllocator> >(
      &decompressor, &writer, input.size(), input.size());

  (void)uncompress_succeeded; // Variable only used in debug builds.
  assert(uncompress_succeeded);

  std::vector<std::string> uncompressed_pieces;
  writer.UnScatter(&uncompressed_pieces);

  std::string uncompressed;
  for (const std::string &piece : uncompressed_pieces) {
    uncompressed.append(piece);
  }

  assert(input == uncompressed);
  return 0;
}