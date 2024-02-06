#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct hash_state src;
  struct hash_state dst;

  // Initialize src with random data
  size_t src_size = stream.ConsumeIntegralInRange<size_t>(0, sizeof(struct hash_state));
  std::vector<uint8_t> src_data = stream.ConsumeBytes<uint8_t>(src_size);
  memcpy(&src, src_data.data(), src_data.size());

  // Call the function under test
  md2_copy(&src, &dst);

  return 0;
}