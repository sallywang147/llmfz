#include <openssl/rsa.h>
#include <openssl/pem.h>

extern "C" {
#include <openssl/err.h>
}

int main() {
  RSA *rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
  if (!rsa) {
    ERR_print_errors_fp(stderr);
    return 1;
  }

  BIO *bio = BIO_new_file("private.pem", "w");
  if (!bio) {
    ERR_print_errors_fp(stderr);
    return 1;
  }

  PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
  BIO_free(bio);

  RSA_free(rsa);

  return 0;
}