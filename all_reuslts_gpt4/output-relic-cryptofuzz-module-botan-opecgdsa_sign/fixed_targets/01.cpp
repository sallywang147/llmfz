#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <optional>

#include "cryptofuzz/module/Botan/operations.h"
#include "cryptofuzz/module/relic/module.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  cryptofuzz::module::Botan botanModule;
  cryptofuzz::module::relic relicModule;

  std::optional<cryptofuzz::component::ECC_PrivateKey> eccPrivateKey;
  std::optional<cryptofuzz::component::ECC_PublicKey> eccPublicKey;
  std::optional<cryptofuzz::component::Bignum> bignum;
  std::optional<cryptofuzz::component::Cleartext> cleartext;

  if (stream.remaining_bytes() > 0) {
    eccPrivateKey = cryptofuzz::component::ECC_PrivateKey(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes())));
  }

  if (stream.remaining_bytes() > 0) {
    eccPublicKey = cryptofuzz::component::ECC_PublicKey(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes())));
  }

  if (stream.remaining_bytes() > 0) {
    bignum = cryptofuzz::component::Bignum(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes())));
  }

  if (stream.remaining_bytes() > 0) {
    cleartext = cryptofuzz::component::Cleartext(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes())));
  }

  cryptofuzz::operation::ECDSA_Sign ecdsaSign(eccPrivateKey, eccPublicKey, bignum, cleartext);

  botanModule.OpECGDSA_Sign(&relicModule, &ecdsaSign);

  return 0;
}