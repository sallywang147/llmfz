#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <optional>
#include "cryptofuzz/module/Botan.h"
#include "cryptofuzz/operation/ECDSA_Sign.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::optional<std::string> opt_string;
  if (fuzzed_data.ConsumeBool()) {
    opt_string = fuzzed_data.ConsumeRandomLengthString();
  }

  cryptofuzz::module::Botan botan_module;
  cryptofuzz::module::relic relic_module;

  uint64_t op1 = fuzzed_data.ConsumeIntegral<uint64_t>();
  uint64_t op2 = fuzzed_data.ConsumeIntegral<uint64_t>();
  std::string op3 = fuzzed_data.ConsumeRandomLengthString();
  std::string op4 = fuzzed_data.ConsumeRandomLengthString();
  std::string op5 = fuzzed_data.ConsumeRandomLengthString();
  std::string op6 = fuzzed_data.ConsumeRandomLengthString();
  std::string op7 = fuzzed_data.ConsumeRandomLengthString();
  std::string op8 = fuzzed_data.ConsumeRandomLengthString();
  std::string op9 = fuzzed_data.ConsumeRandomLengthString();
  std::string op10 = fuzzed_data.ConsumeRandomLengthString();
  std::string op11 = fuzzed_data.ConsumeRandomLengthString();
  
  cryptofuzz::operation::ECDSA_Sign ecdsa_sign(op1, op2, op3, op4, op5, op6, op7, op8, op9, op10, op11);

  botan_module.OpECDSA_Sign(opt_string, &relic_module, &ecdsa_sign);

  return 0;
}