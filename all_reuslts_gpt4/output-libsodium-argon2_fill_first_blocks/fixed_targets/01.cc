#include <fuzzer/FuzzedDataProvider.h>
#include <argon2.h>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Argon2 instance
  Argon2_instance_t instance;
  memset(&instance, 0, sizeof(instance));

  // Initialize the blockhash
  char blockhash[ARGON2_BLOCK_SIZE];
  memset(blockhash, 0, sizeof(blockhash));

  // Fill the first blocks
  argon2_fill_first_blocks(blockhash, &instance);

  return 0;
}