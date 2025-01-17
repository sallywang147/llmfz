 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <openssl/ec.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> input_buffer(provider.ConsumeBytes<uint8_t>(size));
  FILE* input_file = fmemopen(input_buffer.data(), input_buffer.size(), "rb");
  if (input_file == nullptr) {
    return 0;
  }

  struct ec_key_st* key = nullptr;
  PEM_read_ECPrivateKey(input_file, &key, nullptr, nullptr);
  EC_KEY_free(key);
  fclose(input_file);

  return 0;
}