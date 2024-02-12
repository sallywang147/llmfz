 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> input_bytes = provider.ConsumeBytes<uint8_t>(size);
  struct bio_st bio;
  BIO_meth_set_write(&bio, BIO_meth_get_write(BIO_s_mem()));
  BIO_set_mem_buf(&bio, input_bytes.data(), size);
  struct ec_key_st* key = nullptr;
  PEM_read_bio_ECPrivateKey(&bio, &key, nullptr, nullptr);
  BIO_free(&bio);
  EC_KEY_free(key);
  return 0;
}