#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  void *data_ptr = bytes.data();

  FILE* f = fmemopen(data_ptr, size, "r");
  RSA* rsa = nullptr;
  PEM_read_RSAPrivateKey(f, &rsa, nullptr, nullptr);
  RSA_free(rsa);
  fclose(f);

  return 0;
}