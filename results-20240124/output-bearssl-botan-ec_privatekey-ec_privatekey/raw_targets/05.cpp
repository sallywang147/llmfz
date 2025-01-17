 #include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <botan/botan.h>
#include <botan/internal/botan_rng.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> key_data = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  Botan::EC_PrivateKey* key = new Botan::EC_PrivateKey(key_data.data(), key_data.size());

  std::vector<uint8_t> alg_id_data = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  Botan::AlgorithmIdentifier alg_id(alg_id_data.data(), alg_id_data.size());

  std::vector<uint8_t> passwd = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  char* passwd_ptr = reinterpret_cast<char*>(passwd.data());

  std::vector<uint8_t> salt = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  char* salt_ptr = reinterpret_cast<char*>(salt.data());

  size_t iterations = stream.ConsumeIntegralInRange<size_t>(0, std::numeric_limits<size_t>::max());

  bool use_pbkdf2 = stream.ConsumeBool();

  key->EC_PrivateKey(key, &passwd_ptr, &alg_id, salt_ptr, iterations, use_pbkdf2);

  return 0;
}