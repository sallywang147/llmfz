#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>

extern "C" {
#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *fuzz_der = (char *)malloc(size + 1);
  if (fuzz_der == NULL) {
    return 0;
  }
  memcpy(fuzz_der, data, size);
  fuzz_der[size] = '\0';

  struct RSApub pk;
  memset(&pk, 0, sizeof(pk));
  pk.n = mpnew(0);
  pk.e = mpnew(0);

  char *result = X509verify(fuzz_der, size, &pk);

  mpfree(pk.n);
  mpfree(pk.e);
  free(fuzz_der);
  free(result);
  return 0;
}