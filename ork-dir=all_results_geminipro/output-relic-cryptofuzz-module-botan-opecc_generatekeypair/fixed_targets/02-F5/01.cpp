#include <fuzzer/FuzzedDataProvider.h>
#include <cryptofuzz/Botan/Botan.h>
#include <cryptofuzz/module/relic/relic.h>
#include <cryptofuzz/operation/Misc.h>

extern "C" {
#include <botan/botan.h>
}

namespace cryptofuzz {
namespace module {
namespace Botan {

void OpECC_GenerateKeyPair(std::optional<std::string> *curve,
                           module::relic *relic,
                           operation::Misc *misc) {
  FuzzedDataProvider data_provider;
  std::string curve_name = data_provider.ConsumeRandomLengthString(32);
  Botan::AutoSeeded_RNG rng;
  Botan::EC_Group group(curve_name);
  Botan::EC_Key_Pair key_pair(rng, group);
  *curve = curve_name;
  relic->ec_public_key = Botan::EC_PublicKey(group, key_pair.public_key());
  relic->ec_private_key = Botan::EC_PrivateKey(group, key_pair.private_key());
  misc->status = true;
}

}  // namespace Botan
}  // namespace module
}  // namespace cryptofuzz

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);
  cryptofuzz::module::relic relic;
  cryptofuzz::operation::Misc misc;
  cryptofuzz::module::Botan::OpECC_GenerateKeyPair(nullptr, &relic, &misc);
  return 0;
}