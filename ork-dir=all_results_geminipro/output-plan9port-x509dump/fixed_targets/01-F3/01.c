#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
  X509 *x = d2i_X509(NULL, (const unsigned char **)&fuzz_der, size);

  if (x != NULL) {
    X509_free(x);
  }

  free(fuzz_der);
  return 0;
}