#include <openssl/pem.h>
#include <openssl/rsa.h>

extern "C" {
#include <openssl/bio.h>
}

RSA* rsa = PEM_read_bio_RSAPrivateKey(bio, nullptr, nullptr, nullptr);