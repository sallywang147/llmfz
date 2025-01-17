#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libsec.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a random RSA private key
  struct RSApriv* priv = rsagen(1024, 65537, 0, nil);
  if (priv == nullptr) {
    return 0;
  }

  // Consume a string from the data provider
  std::string subj = stream.ConsumeRandomLengthString();
  
  // Declare certlen
  int certlen;

  // Call the target function
  char* cert = X509req(priv, const_cast<char*>(subj.c_str()), &certlen);

  // Free the certificate and private key
  free(cert);
  rsaprivfree(priv);

  return 0;
}