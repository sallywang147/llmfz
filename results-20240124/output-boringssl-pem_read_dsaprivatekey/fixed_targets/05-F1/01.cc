#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

extern "C" {
#include <openssl/bio.h>
#include <openssl/dsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  BIO* bio = BIO_new_mem_buf(const_cast<char*>(input.data()), input.size());
  if (bio == nullptr) {
    return 0;
  }

  DSA* dsa = nullptr;
  DSA** dsa_ptr = &dsa;
  PEM_read_DSAPrivateKey(bio, dsa_ptr, nullptr, nullptr);
  BIO_free(bio);
  DSA_free(dsa);

  return 0;
}