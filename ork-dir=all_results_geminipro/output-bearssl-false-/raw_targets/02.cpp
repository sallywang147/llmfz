#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "cryptofuzz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Botan::ECGDSA_PrivateKey ecdsa_private_key(
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(
          0, stream.remaining_bytes())));
  cryptofuzz::operation::ECDSA_Sign ecdsa_sign;
  std::optional<cryptofuzz::component::ECDSA_Signature> ecdsa_signature;
  cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey,
                                              cryptofuzz::operation::ECGDSA_Sign,
                                              false>(&ecdsa_signature, &ecdsa_sign);
  return 0;
}