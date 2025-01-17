#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>

extern "C" {
#include <authsrv.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *fuzz_der = (char *)malloc(size + 1);
  if (fuzz_der == NULL) {
    return 0;
  }
  memcpy(fuzz_der, data, size);
  fuzz_der[size] = '\0';

  struct Bytes signature;
  signature.data = (uchar *)fuzz_der;
  signature.len = size;

  struct RSApub pk;
  pk.n = mpnew(0);
  pk.e = mpnew(0);

  char *edigest = strdup("SHA1");
  struct Elem **psigalg = (struct Elem **)malloc(sizeof(struct Elem *));
  *psigalg = NULL;

  char *result = verify_signature(&signature, &pk, edigest, psigalg);

  free(result);
  free(fuzz_der);
  free(edigest);
  free(psigalg);
  mpfree(pk.n);
  mpfree(pk.e);

  return 0;
}