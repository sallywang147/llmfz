#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

#include "rsa.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the parameters for verify_signature function
  struct Bytes signature;
  struct RSApub pk;
  char edigest[32];
  struct Elem *psigalg = NULL;

  // Consume data for the parameters
  signature.len = stream.ConsumeIntegralInRange<size_t>(0, size);
  signature.data = (unsigned char *)stream.ConsumeBytes(signature.len).data();

  pk.size = stream.ConsumeIntegralInRange<size_t>(0, size);
  pk.n = (unsigned char *)stream.ConsumeBytes(pk.size).data();
  pk.ek = (unsigned char *)stream.ConsumeBytes(pk.size).data();

  std::string edigest_str = stream.ConsumeBytesAsString(32);
  strncpy(edigest, edigest_str.c_str(), 32);

  // Call the target function
  char * result = verify_signature(&signature, &pk, edigest, &psigalg);

  // Free the allocated memory
  free(result);

  return 0;
}