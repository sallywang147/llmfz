#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "botan/botan.h"
#include "botan/ec_key.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Botan::EC_PrivateKey* ec_private_key = new Botan::EC_PrivateKey();
  std::vector<uint8_t> ec_group_bytes =
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  Botan::EC_Group ec_group(ec_group_bytes.data(), ec_group_bytes.size());
  std::vector<uint8_t> ec_point_bytes =
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  Botan::PointGFp ec_point(ec_group, ec_point_bytes.data(), ec_point_bytes.size());
  std::vector<uint8_t> ec_private_value_bytes =
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  Botan::BigInt ec_private_value(ec_private_value_bytes.data(),
                                 ec_private_value_bytes.size());
  Botan::EC_PrivateKey ec_private_key_copy(ec_group, ec_point, ec_private_value);
  ec_private_key->EC_PrivateKey(&ec_private_key_copy, nullptr, nullptr, nullptr, 0,
                                true);
  delete ec_private_key;
  return 0;
}