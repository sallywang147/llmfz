#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *fuzz_der = (char *)malloc(size + 1);
  if (fuzz_der == NULL) {
    return 0;
  }
  memcpy(fuzz_der, data, size);
  fuzz_der[size] = '\0';

  struct Bytes signature;
  struct RSApub pk;
  char *edigest;
  struct Elem *psigalg;
  char *result;

  signature.len = size;
  signature.data = fuzz_der;
  result = verify_signature(&signature, &pk, edigest, &psigalg);
  free(result);

  free(fuzz_der);
  return 0;
}