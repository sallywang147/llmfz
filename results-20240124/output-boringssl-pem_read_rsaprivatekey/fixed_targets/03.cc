 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string pem = stream.ConsumeRemainingBytesAsString();
  FILE* fp = fmemopen(reinterpret_cast<void*>(const_cast<char*>(pem.c_str())),
                      pem.size(), "r");

  struct rsa_st* rsa = nullptr;
  PEM_read_RSAPrivateKey(fp, &rsa, nullptr, nullptr);
  RSA_free(rsa);
  fclose(fp);
  return 0;
}