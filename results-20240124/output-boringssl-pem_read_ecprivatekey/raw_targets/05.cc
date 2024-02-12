 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <openssl/ec.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* ptr = str.c_str();
  size_t len = str.size();
  struct ec_key_st *key = nullptr;
  PEM_read_ECPrivateKey(nullptr, &key, nullptr, ptr);
  return 0;
}