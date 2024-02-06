#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <optional>

#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/operation/ECDSA_Sign.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::optional<cryptofuzz::component::Bignum> curveType = provider.ConsumeBool() ? std::make_optional<cryptofuzz::component::Bignum>(provider.ConsumeIntegral<uint64_t>()) : std::nullopt;
  std::optional<cryptofuzz::component::Bignum> cleartext = provider.ConsumeBool() ? std::make_optional<cryptofuzz::component::Bignum>(provider.ConsumeIntegral<uint64_t>()) : std::nullopt;
  std::optional<cryptofuzz::component::Bignum> nonce = provider.ConsumeBool() ? std::make_optional<cryptofuzz::component::Bignum>(provider.ConsumeIntegral<uint64_t>()) : std::nullopt;

  cryptofuzz::operation::ECDSA_Sign ecdsaSign(curveType, cleartext, nonce);

  cryptofuzz::module::Botan botanModule;
  cryptofuzz::module::BearSSL bearSSLModule;

  botanModule.OpECGDSA_Sign(&bearSSLModule, &ecdsaSign);

  return 0;
}