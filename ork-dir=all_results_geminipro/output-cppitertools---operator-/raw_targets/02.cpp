#include <fuzzer/FuzzedDataProvider.h>

#include <iterator>
#include <vector>

using iter::Compressed;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::vector<int> v;
  for (int i = 0; i < fdp.ConsumeIntegralInRange<int>(1, 1024); i++) {
    v.push_back(fdp.ConsumeIntegral<int>());
  }
  std::vector<bool> b;
  for (int i = 0; i < fdp.ConsumeIntegralInRange<int>(1, 1024); i++) {
    b.push_back(fdp.ConsumeBool());
  }
  auto c = Compressed<std::vector<int> &, std::vector<bool> &>(v, b);
  auto it = c.begin();
  while (it != c.end()) {
    int *val = *it;
    (void)val;
    it++;
  }
  return 0;
}