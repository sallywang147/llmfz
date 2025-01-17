#include <bitset>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>
#include <iostream>
#include <vector>

namespace phmap {
namespace priv {

extern "C" {
#include <bitset>
#include <cstring>
}

void ConvertDeletedToEmptyAndFullToDeleted(char* ctrl, size_t capacity) {
  if (capacity < 1) {
    return;
  }
  std::bitset<sizeof(char) * 8> ctrl_bits(ctrl, capacity);
  for (size_t i = 0; i < capacity; ++i) {
    if (ctrl_bits.test(i)) {
      ctrl_bits.set(i, false);
    } else {
      ctrl_bits.set(i, true);
    }
  }
}

}  // namespace priv
}  // namespace phmap

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  const size_t capacity = fuzzed_data.ConsumeIntegralInRange<size_t>(0, 10000);
  std::vector<char> ctrl(capacity);
  fuzzed_data.ConsumeBytes(&ctrl[0], capacity);
  phmap::priv::ConvertDeletedToEmptyAndFullToDeleted(&ctrl[0], capacity);
  return 0;
}