 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <openssl/dsa.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  FILE* fp = fmemopen(bytes.data(), bytes.size(), "r");

  DSA* dsa = nullptr;
  PEM_read_DSAPrivateKey(fp, &dsa, nullptr, nullptr);
  DSA_free(dsa);
  fclose(fp);

  return 0;
}