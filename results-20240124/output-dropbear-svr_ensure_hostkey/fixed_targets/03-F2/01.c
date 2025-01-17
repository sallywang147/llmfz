#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <gmp.h> // Include the GMP header for mp_init() and mp_clear()

#include "dropbear.h"

extern "C" {
#include "dropbear.h" // Wrap the dropbear.h header with extern "C" {}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  svr_context context;
  memset(&context, 0, sizeof(context));
  context.hostkey = (sign_key*)malloc(sizeof(sign_key));
  memset(context.hostkey, 0, sizeof(sign_key));
  context.hostkey->type = DROPBEAR_SIGNKEY_RSA;
  context.hostkey->key = (rsa_key*)malloc(sizeof(rsa_key));
  memset(context.hostkey->key, 0, sizeof(rsa_key));

  // Initialize the GMP variables
  context.hostkey->key->p = mpz_init();
  context.hostkey->key->q = mpz_init();
  context.hostkey->key->pub = mpz_init();
  context.hostkey->key->priv = mpz_init();
  context.hostkey->key->iqmp = mpz_init();

  svr_ensure_hostkey(&context);

  // Clear the GMP variables
  mpz_clear(context.hostkey->key->p);
  mpz_clear(context.hostkey->key->q);
  mpz_clear(context.hostkey->key->pub);
  mpz_clear(context.hostkey->key->priv);
  mpz_clear(context.hostkey->key->iqmp);

  free(context.hostkey->key);
  free(context.hostkey);

  return 0;
}