#include <openssl/pem.h>
#include <openssl/dsa.h>
#include <stdio.h>

extern "C"
{
#include <openssl/err.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  BIO *bio = BIO_new_mem_buf(data, size);
  DSA *dsa = PEM_read_DSAPrivateKey(bio, NULL, NULL, NULL);
  if (dsa) {
    DSA_free(dsa);
  }
  BIO_free(bio);
  return 0;
}