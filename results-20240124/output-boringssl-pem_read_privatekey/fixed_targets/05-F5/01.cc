#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "openssl/bio.h"
#include "openssl/evp.h"
#include "openssl/pem.h"

extern "C" {
#include "openssl/pem.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  FILE* file = fopen(filename.c_str(), "rb");
  if (file == nullptr) {
    return 0;
  }

  BIO* bio = BIO_new(BIO_s_file());
  if (bio == nullptr) {
    fclose(file);
    return 0;
  }

  BIO_set_fp(bio, file, BIO_NOCLOSE);

  EVP_PKEY* key = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);

  EVP_PKEY_free(key);
  BIO_free(bio);
  fclose(file);

  return 0;
}