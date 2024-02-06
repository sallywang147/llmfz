#include <fuzzer/FuzzedDataProvider.h>
#include <botan/ecdsa.h>
#include <botan/oids.h>
#include <botan/auto_rng.h>
#include <optional>
#include "cryptofuzz/operations.h"
#include "cryptofuzz/module.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Botan::AutoSeeded_RNG rng;
  std::optional<Botan::ECGDSA_PrivateKey> privateKey;
  std::optional<cryptofuzz::operation::ECDSA_Sign> operation;

  // Generate a random ECDSA key
  try {
    Botan::OID oid(stream.ConsumeBytesAsString(10));
    privateKey = Botan::ECGDSA_PrivateKey(rng, oid);
  } catch (...) {
    return 0;
  }

  // Generate a random operation
  try {
    std::vector<uint8_t> toSign = stream.ConsumeBytes<uint8_t>(32);
    operation = cryptofuzz::operation::ECDSA_Sign(toSign);
  } catch (...) {
    return 0;
  }

  // Call the function
  try {
    std::optional<cryptofuzz::component::ECDSA_Signature> signature = cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey, cryptofuzz::operation::ECGDSA_Sign, false>(privateKey, operation);
  } catch (...) {
    return 0;
  }

  return 0;
}