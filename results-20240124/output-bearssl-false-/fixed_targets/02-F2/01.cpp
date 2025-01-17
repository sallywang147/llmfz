#include <cstddef>
#include <cstdint>
#include <memory>

#include "fuzzer/FuzzedDataProvider.h"

#include "cryptofuzz/component/ECDSA_Signature.h"
#include "cryptofuzz/module/Botan_detail.h"
#include "cryptofuzz/operation/ECGDSA_Sign.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::optional<cryptofuzz::component::ECDSA_Signature> signature;
  cryptofuzz::operation::ECDSA_Sign operation;
  cryptofuzz::module::Botan_detail::ECxDSA_Sign<Botan::ECGDSA_PrivateKey, cryptofuzz::operation::ECGDSA_Sign, false>(&signature, &operation, stream);
  return 0;
}

int main() {
  return 0;
}