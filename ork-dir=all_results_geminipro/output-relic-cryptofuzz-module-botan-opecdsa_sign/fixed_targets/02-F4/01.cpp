#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/module/relic.h"

extern "C" {
#include "cryptofuzz/operation/ECDSA_Sign.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  cryptofuzz::module::Botan::OpECDSA_Sign(nullptr, nullptr, stream.ConsumeRemainingBytes());

  return 0;
}