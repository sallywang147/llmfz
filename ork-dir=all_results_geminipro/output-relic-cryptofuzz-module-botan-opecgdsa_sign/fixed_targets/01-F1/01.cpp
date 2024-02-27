#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>

#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/module/relic.h"
#include "cryptofuzz/operation/ECDSA_Sign.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::optional<std::string> hash_algorithm = stream.ConsumeBool()
                                                  ? std::make_optional(stream.ConsumeRandomLengthString())
                                                  : std::nullopt;
  std::unique_ptr<cryptofuzz::module::relic> relic_module =
      std::make_unique<cryptofuzz::module::relic>();
  std::unique_ptr<cryptofuzz::operation::ECDSA_Sign> ecdsa_sign_operation =
      std::make_unique<cryptofuzz::operation::ECDSA_Sign>();
  cryptofuzz::module::Botan::OpECGDSA_Sign(hash_algorithm, relic_module.get(),
                                           ecdsa_sign_operation.get());
  return 0;
}