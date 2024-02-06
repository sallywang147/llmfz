#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "argon2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the Argon2 instance.
  Argon2_instance_t instance;
  instance.version = ARGON2_VERSION_NUMBER;
  instance.memory = nullptr;
  instance.passes = stream.ConsumeIntegral<uint32_t>();
  instance.memory_blocks = stream.ConsumeIntegral<uint32_t>();
  instance.segment_length = stream.ConsumeIntegral<uint32_t>();
  instance.lane_length = stream.ConsumeIntegral<uint32_t>();
  instance.lanes = stream.ConsumeIntegral<uint32_t>();
  instance.threads = stream.ConsumeIntegral<uint32_t>();
  instance.type = Argon2_d;

  // Initialize the blockhash.
  std::string blockhash = stream.ConsumeRemainingBytesAsString();

  // Call the target function.
  argon2_fill_first_blocks(blockhash.data(), &instance);

  return 0;
}