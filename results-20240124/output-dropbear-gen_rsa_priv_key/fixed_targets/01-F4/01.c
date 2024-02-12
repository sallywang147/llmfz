#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bn.h>
#include <openssl/dh.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>

#include <dropbear/dropbear.h>
#include <dropbear/dss.h>
#include <dropbear/dss_sign.h>
#include <dropbear/rsa.h>
#include <dropbear/sha256.h>

extern "C" {
#include <dropbear/dropbear.h>
#include <dropbear/dss.h>
#include <dropbear/dss_sign.h>
#include <dropbear/rsa.h>
#include <dropbear/sha256.h>
}

static void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct dropbear_DSS_Key *key = gen_rsa_priv_key(2048);
  sign_key_free(key);
}