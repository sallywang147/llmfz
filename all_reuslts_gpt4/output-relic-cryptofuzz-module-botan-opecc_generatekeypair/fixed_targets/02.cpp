#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cryptofuzz/operations.h"
#include "cryptofuzz/module.h"
#include "cryptofuzz/module/relic.h"
#include "cryptofuzz/module/botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  std::optional<cryptofuzz::component::ECC_PrivateKey> ecc_private_key;
  std::optional<cryptofuzz::component::ECC_PublicKey> ecc_public_key;
  
  cryptofuzz::module::relic relicModule;
  cryptofuzz::module::Botan botanModule;
  
  cryptofuzz::operation::ECC_GenerateKeyPair ecc_generate_key_pair(0, provider.ConsumeIntegral<uint64_t>());

  botanModule.OpECC_GenerateKeyPair(&ecc_private_key, &relicModule, &ecc_generate_key_pair);
  
  return 0;
}