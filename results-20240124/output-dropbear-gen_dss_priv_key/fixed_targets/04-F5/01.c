#include <openssl/ssl.h>
#include <openssl/err.h>

extern "C" {
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
}

int main() {
  // Generate a 2048-bit DSA private key
  DSA *dsa = DSA_new();
  if (!dsa) {
    ERR_print_errors_fp(stderr);
    return 1;
  }

  if (!DSA_generate_parameters_ex(dsa, 2048, NULL, 0, NULL, NULL, NULL)) {
    ERR_print_errors_fp(stderr);
    DSA_free(dsa);
    return 1;
  }

  if (!DSA_generate_key(dsa)) {
    ERR_print_errors_fp(stderr);
    DSA_free(dsa);
    return 1;
  }

  // Save the private key to a file
  BIO *bio = BIO_new_file("private.pem", "w");
  if (!bio) {
    ERR_print_errors_fp(stderr);
    DSA_free(dsa);
    return 1;
  }

  if (!PEM_write_bio_DSAPrivateKey(bio, dsa, NULL, NULL, 0, NULL, NULL)) {
    ERR_print_errors_fp(stderr);
    BIO_free(bio);
    DSA_free(dsa);
    return 1;
  }

  BIO_free(bio);
  DSA_free(dsa);

  return 0;
}