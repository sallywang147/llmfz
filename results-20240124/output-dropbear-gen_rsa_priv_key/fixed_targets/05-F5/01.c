#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bn.h>
#include <openssl/dh.h>
#include <openssl/dsa.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include <libssh/libssh.h>
#include <libssh/server.h>

#include "dropbear_fuzz.h"

extern "C" {
#include "dropbear.h"
#include "dropbear_dss.h"
#include "dropbear_ecdh.h"
#include "dropbear_ed25519.h"
#include "dropbear_hostkey.h"
#include "dropbear_kex.h"
#include "dropbear_random.h"
#include "dropbear_rsa.h"
#include "dropbear_server.h"
#include "dropbear_sha256.h"
#include "dropbear_util.h"
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  dropbear_fuzz_test(data, size);
  struct dropbear_DSS_Key *key = gen_rsa_priv_key(1024);
  dropbear_key_free(key);
  return 0;
}