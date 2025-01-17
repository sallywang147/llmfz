#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <optional>

#include "cryptofuzz/operations.h"
#include "cryptofuzz/module/libecc.h"
#include "cryptofuzz/module/botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  cryptofuzz::module::Botan botanModule;
  std::optional<cryptofuzz::component::Bignum> optBignum;
  cryptofuzz::module::libecc libeccModule;

  // Consume data for ECDSA_Sign operation
  std::optional<cryptofuzz::component::ECC_PrivateKey> privKey;
  std::optional<cryptofuzz::component::Bignum> bn;
  std::optional<cryptofuzz::component::Cleartext> ct;

  if (stream.remaining_bytes() > 0) {
    privKey = cryptofuzz::component::ECC_PrivateKey(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes())));
  }

  if (stream.remaining_bytes() > 0) {
    bn = cryptofuzz::component::Bignum(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes())));
  }

  if (stream.remaining_bytes() > 0) {
    ct = cryptofuzz::component::Cleartext(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes())));
  }

  cryptofuzz::operation::ECDSA_Sign ecdsaSign(privKey, bn, ct);

  botanModule.OpECDSA_Sign(optBignum, &libeccModule, &ecdsaSign);

  return 0;
}