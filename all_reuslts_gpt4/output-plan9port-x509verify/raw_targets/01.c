#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <auth.h>
#include <libc.h>
#include <libsec.h>
#include <mp.h>
#include <u.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize FuzzedDataProvider.
  FuzzedDataProvider stream(data, size);

  // Consume data for 'cert' parameter.
  std::string cert_str = stream.ConsumeRandomLengthString();
  char *cert = strdup(cert_str.c_str());

  // Consume data for 'ncert' parameter.
  int ncert = stream.ConsumeIntegral<int>();

  // Prepare 'pk' parameter.
  struct RSApub *pk = (struct RSApub *)malloc(sizeof(struct RSApub));
  if (pk == NULL) {
    free(cert);
    return 0;
  }

  // Consume data for 'pk' parameter.
  pk->n = mpnew(0);
  pk->ek = mpnew(0);
  if (pk->n == NULL || pk->ek == NULL) {
    free(cert);
    free(pk);
    return 0;
  }

  // Call the target function.
  char *result = X509verify(cert, ncert, pk);

  // Cleanup.
  free(cert);
  mpfree(pk->n);
  mpfree(pk->ek);
  free(pk);
  if (result != NULL) {
    free(result);
  }

  return 0;
}