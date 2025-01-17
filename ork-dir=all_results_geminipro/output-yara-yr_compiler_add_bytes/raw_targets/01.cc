#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "yacc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  YR_COMPILER* compiler = yr_compiler_new();
  if (compiler == nullptr) {
    return 0;
  }

  const size_t rules_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> rules_data = stream.ConsumeBytes<uint8_t>(rules_size);
  const size_t namespace_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> namespace_data = stream.ConsumeBytes<uint8_t>(namespace_size);

  int ret = yr_compiler_add_bytes(compiler, reinterpret_cast<char*>(rules_data.data()),
                                 rules_size, reinterpret_cast<char*>(namespace_data.data()));
  yr_compiler_delete(compiler);
  return ret;
}