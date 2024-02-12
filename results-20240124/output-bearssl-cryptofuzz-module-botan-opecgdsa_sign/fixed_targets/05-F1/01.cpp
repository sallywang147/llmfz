#include <cstddef>
#include <cstdint>
#include <memory>

#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/module/BearSSL.h"
#include "cryptofuzz/operation/ECDSA_Sign.h"

extern "C" {
#include "cryptofuzz/Cryptofuzz.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  cryptofuzz::module::Botan botan;
  cryptofuzz::module::BearSSL bearssl;
  cryptofuzz::operation::ECDSA_Sign ecdsa_sign;
  std::optional<cryptofuzz::module::BearSSL> bearssl_opt;
  bearssl_opt = bearssl;
  botan.OpECGDSA_Sign(&bearssl_opt, &ecdsa_sign);
  return 0;
}