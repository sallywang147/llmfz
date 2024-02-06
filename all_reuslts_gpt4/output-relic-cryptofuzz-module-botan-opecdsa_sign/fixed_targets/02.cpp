#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/operation/ECDSA_Sign.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Botan module
  cryptofuzz::module::Botan botanModule;

  // Initialize Relic module
  cryptofuzz::module::relic relicModule;

  // Initialize ECDSA_Sign operation
  cryptofuzz::operation::ECDSA_Sign ecdsaSignOperation;

  // Extract data for ECDSA_Sign operation
  ecdsaSignOperation.curveType = stream.ConsumeIntegral<uint64_t>();
  ecdsaSignOperation.cleartext = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2);
  ecdsaSignOperation.privkey = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());

  // Call the function
  std::optional<std::vector<uint8_t>> result;
  botanModule.OpECDSA_Sign(&result, &relicModule, &ecdsaSignOperation);

  return 0;
}