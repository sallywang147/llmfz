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

  snappy::SnappySinkAllocator::Datablock iov[1];
  iov[0].iov_base = &input[0];
  iov[0].iov_len = input.size();

  bool uncompress_succeeded = snappy::RawUncompressToIOVec(compressed.data(), compressed.size(), iov, 1);

  (void)uncompress_succeeded; // Variable only used in debug builds.
  assert(uncompress_succeeded);
  assert(input == std::string(reinterpret_cast<char *>(iov[0].iov_base), iov[0].iov_len));
  return 0;
}