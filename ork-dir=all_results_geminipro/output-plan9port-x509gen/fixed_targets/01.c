#include <stdlib.h>
#include <string.h>

#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>

extern "C" {
#include <asn1.h>
#include <rsa.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *fuzz_der = (char *)malloc(size + 1);
  if (fuzz_der == NULL) {
    return 0;
  }
  memcpy(fuzz_der, data, size);
  fuzz_der[size] = '\0';
  asn1dump(fuzz_der, size);

  struct RSApriv *priv = rsaprivnew();
  if (priv == NULL) {
    free(fuzz_der);
    return 0;
  }

  char *cert = X509gen(priv, fuzz_der, NULL, NULL);
  if (cert == NULL) {
    free(fuzz_der);
    rsaprivdestroy(priv);
    return 0;
  }

  // Fix: Free the allocated memory for the certificate before returning.
  free(cert);

  free(fuzz_der);
  rsaprivdestroy(priv);
  return 0;
}