#include <fuzzer/FuzzedDataProvider.h>
#include <libsec.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct RSApriv priv;
  size_t valid = stream.ConsumeIntegral<size_t>();
  int certlen = stream.ConsumeIntegral<int>();
  
  std::string subj = stream.ConsumeRemainingBytesAsString();
  
  X509gen(&priv, subj.c_str(), &valid, &certlen);

  return 0;
}