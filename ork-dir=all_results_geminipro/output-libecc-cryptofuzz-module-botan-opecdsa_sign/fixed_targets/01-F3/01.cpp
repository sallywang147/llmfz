#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "botan_ecdsa_sign.h"

#include <botan/botan.h>

extern "C" {
#include <botan/botan.h>
}

namespace cryptofuzz {
namespace module {
class Botan {
 public:
  static LibECC* LibECC() { return new Botan::LibECC(); }
  class LibECC {
   public:
    LibECC() { Botan::LibraryInitializer init; }
    ~LibECC() {}
  };
};
}  // namespace module

namespace operation {
class Botan {
 public:
  static ECDSA_Sign* ECDSA_Sign() { return new Botan::ECDSA_Sign(); }
  class ECDSA_Sign {
   public:
    ECDSA_Sign() {}
    ~ECDSA_Sign() {}
    bool Sign(const std::string& hash_algorithm, const std::string& private_key,
              std::string* signature) {
      Botan::AutoSeeded_RNG rng;
      Botan::EC_PrivateKey ec_private_key(rng, private_key);
      Botan::PK_Signer signer(ec_private_key, hash_algorithm);
      Botan::secure_vector<uint8_t> output;
      signer.sign(rng, "Hello World", output);
      *signature = std::string(output.begin(), output.end());
      return true;
    }
  };
};
}  // namespace operation
}  // namespace cryptofuzz

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