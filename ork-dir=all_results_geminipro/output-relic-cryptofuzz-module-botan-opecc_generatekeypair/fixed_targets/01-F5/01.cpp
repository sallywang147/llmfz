#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/module/relic.h"
#include "cryptofuzz/operation/Misc.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::optional<std::string> key_type =
      stream.ConsumeBool() ? std::nullopt : stream.ConsumeRandomLengthString();
  cryptofuzz::module::relic* relic_ptr =
      new cryptofuzz::module::relic(stream.ConsumeIntegral<int>());
  cryptofuzz::operation::Misc* misc_ptr =
      new cryptofuzz::operation::Misc(stream.ConsumeIntegral<int>());
  cryptofuzz::module::Botan::OpECC_GenerateKeyPair(key_type, relic_ptr, misc_ptr);
  delete relic_ptr;
  delete misc_ptr;
  return 0;
}