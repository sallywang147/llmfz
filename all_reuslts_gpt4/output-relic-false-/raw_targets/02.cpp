#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <optional>

#include "botan/ec_group.h"
#include "botan/ecdsa.h"
#include "botan/oids.h"
#include "botan/pubkey.h"
#include "botan/rng.h"
#include "cryptofuzz/operations.h"
#include "cryptofuzz/module.h"
#include "cryptofuzz/util.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Botan library
  static bool initialized = false;
  if (!initialized) {
    Botan::LibraryInitializer::initialize();
    initialized = true;
  }

  // Initialize RNG
  Botan::AutoSeeded_RNG rng;

  // Create a ECDSA private key
  const Botan::EC_Group ec_group(Botan::OID("1.2.840.10045.3.1.7")); // secp256r1
  Botan::ECGDSA_PrivateKey private_key(rng, ec_group);

  // Create a cryptofuzz operation
  cryptofuzz::operation::ECGDSA_Sign operation;

  // Initialize the operation with random data
  operation.curveType = stream.ConsumeIntegral<uint64_t>();
  operation.cleartext = cryptofuzz::util::BinToDec(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 64)));
  operation.privkey = cryptofuzz::util::BinToDec(stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 64)));

  // Call the function
  cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey, cryptofuzz::operation::ECGDSA_Sign, false>(&private_key, &operation);

  return 0;
}