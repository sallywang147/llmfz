#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cryptofuzz/operation.h"
#include "cryptofuzz/module.h"
#include "cryptofuzz/component.h"
#include "botan/ecgdsa.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a Botan::ECGDSA_PrivateKey object
  Botan::ECGDSA_PrivateKey privateKey;

  // Create a cryptofuzz::operation::ECDSA_Sign object
  std::optional<cryptofuzz::operation::ECDSA_Sign> ecdsaSign;

  // Call the function to fuzz
  cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey, cryptofuzz::operation::ECGDSA_Sign, false>(&privateKey, &ecdsaSign);

  return 0;
}