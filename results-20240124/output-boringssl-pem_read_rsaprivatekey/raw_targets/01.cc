 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <openssl/pem.h>
#include <openssl/rsa.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> pem_data = stream.ConsumeRemainingBytes();
  BIO* bio = BIO_new_mem_buf(pem_data.data(), pem_data.size());
  if (bio == nullptr) {
    return 0;
  }

  RSA* rsa = nullptr;
  PEM_read_RSAPrivateKey(bio, &rsa, nullptr, nullptr);
  BIO_free(bio);

  if (rsa != nullptr) {
    RSA_free(rsa);
  }

  return 0;
}