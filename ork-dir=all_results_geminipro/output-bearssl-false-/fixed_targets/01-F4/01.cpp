#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "botan/botan.h"
#include "botan/ecdsa.h"
#include "botan/hash.h"
#include "botan/rng.h"

using namespace Botan;

namespace cryptofuzz {
namespace module {
namespace Botan_detail {

extern "C" {
namespace {
template <typename PrivateKey, typename Op, bool Verify>
void ECxDSA_Sign(std::optional<component::ECDSA_Signature>* signature,
                 Op* operation) {
  auto rng = std::make_unique<AutoSeeded_RNG>();

  PrivateKey key(rng.get());

  std::vector<uint8_t> message = operation->message();
  auto hash_name = operation->hash_function();
  auto hash = MessageAuthenticationCode::create(hash_name, rng.get());
  hash->update(message.data(), message.size());
  auto digest = hash->final();

  if (!Verify) {
    auto sig = key.sign(*digest, rng.get());
    signature->emplace(sig);
  } else {
    auto sig = operation->signature();
    signature->emplace(sig);
    key.verify(*digest, sig);
  }
}
}  // namespace
}  // extern "C"

}  // namespace Botan_detail
}  // namespace module
}  // namespace cryptofuzz

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> message = stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange(0, 1024));
  std::string hash_name =
      stream.PickValueInArray({"SHA-256", "SHA-512", "SHA3-256", "SHA3-512"});

  auto operation =
      std::make_unique<cryptofuzz::operation::ECGDSA_Sign>(message, hash_name);

  std::optional<cryptofuzz::component::ECDSA_Signature> signature;
  cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey,
                                                 cryptofuzz::operation::ECGDSA_Sign,
                                                 false>(&signature, operation.get());
  cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey,
                                                 cryptofuzz::operation::ECGDSA_Sign,
                                                 true>(&signature, operation.get());

  return 0;
}