#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

extern "C" {
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_values = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<int> values;
  for (size_t i = 0; i < num_values; ++i) {
    values.push_back(stream.ConsumeIntegral<int>());
  }
  _GLOBAL__sub_I_unpack_pack_fuzzer_cpp(values.data(), values.size());
  return 0;
}