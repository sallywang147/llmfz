#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <openssl/ec.h>
#include <openssl/pem.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string pem_data = stream.ConsumeRemainingBytesAsString();
  BIO* bio = BIO_new_mem_buf(pem_data.data(), pem_data.size());
  if (bio == nullptr) {
    return 0;
  }

  EC_KEY *key = PEM_read_bio_ECPrivateKey(bio, nullptr, nullptr, nullptr);
  if (key == nullptr) {
    return 0;
  }

  EC_KEY_free(key);
  BIO_free(bio);
  return 0;
}