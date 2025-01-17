#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libsec.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int ncert = stream.ConsumeIntegral<int>();
  std::string cert = stream.ConsumeRemainingBytesAsString();

  struct RSApub *pk = rsagen(512, 3, 0);  // Generate a dummy RSA public key

  X509verify(const_cast<char*>(cert.c_str()), ncert, pk);

  rsapubfree(pk);

  return 0;
}