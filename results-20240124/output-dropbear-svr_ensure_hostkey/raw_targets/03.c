 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "dropbear.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  svr_context context;
  memset(&context, 0, sizeof(context));
  context.hostkey = (sign_key*)malloc(sizeof(sign_key));
  memset(context.hostkey, 0, sizeof(sign_key));
  context.hostkey->type = DROPBEAR_SIGNKEY_RSA;
  context.hostkey->key = (rsa_key*)malloc(sizeof(rsa_key));
  memset(context.hostkey->key, 0, sizeof(rsa_key));
  context.hostkey->key->p = mp_init();
  context.hostkey->key->q = mp_init();
  context.hostkey->key->pub = mp_init();
  context.hostkey->key->priv = mp_init();
  context.hostkey->key->iqmp = mp_init();

  svr_ensure_hostkey(&context);

  mp_clear(context.hostkey->key->p);
  mp_clear(context.hostkey->key->q);
  mp_clear(context.hostkey->key->pub);
  mp_clear(context.hostkey->key->priv);
  mp_clear(context.hostkey->key->iqmp);
  free(context.hostkey->key);
  free(context.hostkey);

  return 0;
}