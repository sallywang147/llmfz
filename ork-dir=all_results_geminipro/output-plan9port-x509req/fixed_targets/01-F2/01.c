#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>

extern "C" {
#include <lib9.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *fuzz_der = (char *)malloc(size + 1);
  if (fuzz_der == NULL) {
    return 0;
  }
  memcpy(fuzz_der, data, size);
  fuzz_der[size] = '\0';

  struct RSApriv *priv = rsaprivnew();
  if (priv == NULL) {
    free(fuzz_der);
    return 0;
  }

  char *cert = X509req(priv, fuzz_der, NULL);
  if (cert == NULL) {
    rsaprivfree(priv);
    free(fuzz_der);
    return 0;
  }

  free(fuzz_der);
  free(cert);
  rsaprivfree(priv);
  return 0;
}