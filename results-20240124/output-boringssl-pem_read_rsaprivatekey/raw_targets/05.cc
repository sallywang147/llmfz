 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BIO* bio = BIO_new_mem_buf(data, size);
  if (bio == nullptr) {
    return 0;
  }

  RSA* rsa = PEM_read_RSAPrivateKey(bio, nullptr, nullptr, nullptr);
  if (rsa == nullptr) {
    ERR_print_errors_fp(stderr);
  }

  RSA_free(rsa);
  BIO_free(bio);
  return 0;
}