#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "botan/ec_group.h"
#include "botan/ec_privatekey.h"
#include "botan/alg_id.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an EC group
  Botan::EC_Group group("secp256r1");

  // Consume data for the private key
  std::vector<uint8_t> private_key_vector = stream.ConsumeBytes<uint8_t>(32);
  Botan::BigInt private_key(private_key_vector.data(), private_key_vector.size());

  // Create the private key
  Botan::EC_PrivateKey ec_private_key(group, private_key);

  // Consume data for the parameters
  std::vector<char*> params_vector;
  while (stream.remaining_bytes() > 0) {
    std::string param = stream.ConsumeRandomLengthString();
    params_vector.push_back(const_cast<char*>(param.c_str()));
  }
  char** params = params_vector.data();

  // Create an AlgorithmIdentifier
  Botan::AlgorithmIdentifier alg_id;

  // Consume data for the buffer and the boolean
  std::string buffer = stream.ConsumeRandomLengthString();
  bool boolean = stream.ConsumeBool();

  // Call the function
  ec_private_key.EC_PrivateKey(&ec_private_key, params, &alg_id, buffer.data(), buffer.size(), boolean);

  return 0;
}