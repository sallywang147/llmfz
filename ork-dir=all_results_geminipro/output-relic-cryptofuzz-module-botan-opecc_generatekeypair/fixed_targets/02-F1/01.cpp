#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/module/relic.h"
#include "cryptofuzz/operation/Misc.h"

extern "C" {
#include "cryptofuzz/operation/ECC.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::optional<std::string> opt_str;
  cryptofuzz::module::relic relic_obj;
  cryptofuzz::operation::Misc misc_obj;
  cryptofuzz::operation::ECC::OpECC_GenerateKeyPair(&opt_str, &relic_obj,
                                                   &misc_obj);
  return 0;
}