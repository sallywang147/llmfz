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

  cryptofuzz::module::libecc* libecc_ptr = new cryptofuzz::module::libecc();
  std::optional<cryptofuzz::module::libecc>* libecc_opt =
      new std::optional<cryptofuzz::module::libecc>(*libecc_ptr);

  cryptofuzz::operation::ECDSA_Sign* ecdsa_sign_ptr =
      new cryptofuzz::operation::ECDSA_Sign();
  std::optional<cryptofuzz::operation::ECDSA_Sign>* ecdsa_sign_opt =
      new std::optional<cryptofuzz::operation::ECDSA_Sign>(*ecdsa_sign_ptr);

  cryptofuzz::module::Botan::OpECDSA_Sign(libecc_opt, libecc_ptr, ecdsa_sign_opt);

  delete libecc_opt;
  delete libecc_ptr;
  delete ecdsa_sign_opt;
  delete ecdsa_sign_ptr;

  return 0;
}