#include <ptls/ptls.h>

extern "C" {
#include <ptls/fuzz.h>
#include <ptls/certs.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ptls_fuzz_server(data, size);
  return 0;
}