#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cryptofuzz.h"
#include "cryptofuzz/module/Botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::optional<cryptofuzz::module::libecc> libecc_opt =
      cryptofuzz::module::Botan::CreateLibecc();
  if (!libecc_opt) {
    return 0;
  }
  cryptofuzz::module::libecc* libecc_ptr = &*libecc_opt;

  std::optional<cryptofuzz::operation::ECDSA_Sign> ecdsa_sign_opt =
      cryptofuzz::module::Botan::CreateECDSA_Sign();
  if (!ecdsa_sign_opt) {
    return 0;
  }
  cryptofuzz::operation::ECDSA_Sign* ecdsa_sign_ptr = &*ecdsa_sign_opt;

  cryptofuzz::module::Botan::OpECDSA_Sign(libecc_opt, libecc_ptr, ecdsa_sign_opt);

  return 0;
}