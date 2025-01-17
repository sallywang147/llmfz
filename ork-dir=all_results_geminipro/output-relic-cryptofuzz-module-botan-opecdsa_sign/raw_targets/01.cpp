#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <string>

#include "cryptofuzz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::optional<std::string> msg = stream.ConsumeRemainingBytesAsString();
  cryptofuzz::module::relic relic;
  cryptofuzz::operation::ECDSA_Sign ecdsa_sign;
  cryptofuzz::module::Botan::OpECDSA_Sign(&msg, &relic, &ecdsa_sign);
  return 0;
}