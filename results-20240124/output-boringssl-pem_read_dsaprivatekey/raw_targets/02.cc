 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <openssl/dsa.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  DSA* dsa = nullptr;
  BIO* bio = BIO_new_mem_buf(data, size);
  PEM_read_DSAPrivateKey(bio, &dsa, nullptr, nullptr);
  BIO_free(bio);
  DSA_free(dsa);
  return 0;
}