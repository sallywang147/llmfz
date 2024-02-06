#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "botan_ecdsa_sign.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::optional<std::string> hash_algorithm = stream.ConsumeBool()
                                                  ? stream.ConsumeEnum<std::string>()
                                                  : std::nullopt;
  cryptofuzz::module::libecc* libecc_ptr =
      stream.PickValueInArray({&cryptofuzz::module::Botan::LibECC(),
                              &cryptofuzz::module::OpenSSL::LibECC()});
  cryptofuzz::operation::ECDSA_Sign* ecdsa_sign_ptr =
      stream.PickValueInArray({&cryptofuzz::operation::Botan::ECDSA_Sign(),
                              &cryptofuzz::operation::OpenSSL::ECDSA_Sign()});

  cryptofuzz::module::Botan::OpECDSA_Sign(hash_algorithm, libecc_ptr,
                                        ecdsa_sign_ptr);
  return 0;
}