#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "cryptofuzz.h"

extern "C" {
#include "botan_ecdsa.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  cryptofuzz::module::Botan::OpECGDSA_Sign(nullptr, nullptr, nullptr);
  return 0;
}