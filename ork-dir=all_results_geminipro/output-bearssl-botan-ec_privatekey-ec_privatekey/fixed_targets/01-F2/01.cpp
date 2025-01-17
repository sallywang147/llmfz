#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include <botan/botan.h>
#include <botan/ecdsa.h>
#include <botan/pubkey.h>
#include <botan/rng.h>

extern "C" {
#include <botan/pkcs8.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string key_type = stream.PickValueInArray({"secp256r1", "secp384r1", "secp521r1"});
  Botan::AutoSeeded_RNG rng;
  Botan::EC_Group group(key_type);
  Botan::EC_PrivateKey key(rng, group);
  Botan::PK_Encryptor_EME encryptor(key);

  std::vector<uint8_t> output;
  encryptor.encrypt(stream.ConsumeRemainingBytes(), output, rng);
  return 0;
}