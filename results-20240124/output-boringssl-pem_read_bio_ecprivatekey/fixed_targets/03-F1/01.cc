#include <fuzzer/FuzzedDataProvider.h>

#include <openssl/bio.h>
#include <openssl/ec.h>
#include <openssl/pem.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> input_bytes = provider.ConsumeBytes<uint8_t>(size);
  BIO* bio = BIO_new(BIO_s_mem());
  BIO_write(bio, input_bytes.data(), size);
  EC_KEY* key = nullptr;
  PEM_read_bio_ECPrivateKey(bio, &key, nullptr, nullptr);
  BIO_free(bio);
  EC_KEY_free(key);
  return 0;
}