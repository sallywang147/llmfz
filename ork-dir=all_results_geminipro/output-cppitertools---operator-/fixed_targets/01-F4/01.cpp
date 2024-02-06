#include <fuzzer/FuzzedDataProvider.h>
#include <iterator>
#include <vector>

extern "C" {
#include <iterator>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::vector<int> v;
  std::vector<bool> b;
  for (int i = 0; i < fdp.ConsumeIntegralInRange<int>(1, 1024); i++) {
    v.push_back(fdp.ConsumeIntegral<int>());
    b.push_back(fdp.ConsumeBool());
  }
  auto c = compress(v, b);
  auto it = c.begin();
  int *p = &*it;
  *p;  // This line fixes the issue.
  return 0;
}
}