 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <openssl/bio.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  BIO *bio = BIO_new_mem_buf(const_cast<uint8_t*>(data), size);
  if (bio == nullptr) {
    return 0;
  }

  DSA *dsa = nullptr;
  PEM_read_DSAPrivateKey(bio, &dsa, nullptr, nullptr);
  DSA_free(dsa);
  BIO_free(bio);
  return 0;
}