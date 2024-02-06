#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "cryptofuzz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::optional<std::string> key = stream.ConsumeRemainingBytesAsString();
  cryptofuzz::module::BearSSL* bearssl =
      new cryptofuzz::module::BearSSL(stream.ConsumeIntegral<uint8_t>());
  cryptofuzz::operation::ECDSA_Sign* ecdsa_sign =
      new cryptofuzz::operation::ECDSA_Sign(stream.ConsumeIntegral<uint8_t>());

  cryptofuzz::module::Botan::OpECGDSA_Sign(key, bearssl, ecdsa_sign);
  return 0;
}