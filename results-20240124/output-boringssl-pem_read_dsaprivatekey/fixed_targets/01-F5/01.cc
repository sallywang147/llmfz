#include <openssl/pem.h>
#include <openssl/dsa.h>

extern "C" {
#include <openssl/err.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  BIO *bio = BIO_new_mem_buf(data, size);
  if (!bio) {
    return 0;
  }
  DSA *dsa = PEM_read_DSAPrivateKey(bio, NULL, NULL, NULL);
  if (!dsa) {
    ERR_print_errors_fp(stderr);
  }
  DSA_free(dsa);
  BIO_free(bio);
  return 0;
}