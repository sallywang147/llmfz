#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int mz_crypt_aes_set_decrypt_key(char * handle, char * key, int key_length, char * iv, int iv_length);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t key_length = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string key = stream.ConsumeBytesAsString(key_length);
  
  const size_t iv_length = stream.remaining_bytes();
  std::string iv = stream.ConsumeRemainingBytesAsString();

  char handle;
  mz_crypt_aes_set_decrypt_key(&handle, key.data(), key.size(), iv.data(), iv.size());

  return 0;
}