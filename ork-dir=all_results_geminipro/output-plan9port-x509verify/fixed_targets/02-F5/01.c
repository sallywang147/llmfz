#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>

extern "C" {
#include <openssl/pem.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *fuzz_der = (char *)malloc(size + 1);
  if (fuzz_der == NULL) {
    return 0;
  }
  memcpy(fuzz_der, data, size);
  fuzz_der[size] = '\0';

  struct RSApub *pk = rsapuballoc();
  if (pk == NULL) {
    free(fuzz_der);
    return 0;
  }

  char *result = X509verify(fuzz_der, size, pk);
  free(fuzz_der);
  free(pk);
  free(result);  // Free the memory allocated by X509verify
  return 0;
}