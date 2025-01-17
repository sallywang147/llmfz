#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "mz_crypt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char handle[16];
  std::string key = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  int key_length = key.size();
  std::string iv = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size - key_length));
  int iv_length = iv.size();

  mz_crypt_aes_set_decrypt_key(handle, const_cast<char*>(key.c_str()), key_length, const_cast<char*>(iv.c_str()), iv_length);

  return 0;
}