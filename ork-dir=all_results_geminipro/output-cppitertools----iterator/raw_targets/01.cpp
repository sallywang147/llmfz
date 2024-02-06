#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

#include "iter.hpp"

using iter::Combinator;

void FuzzCombinator(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string s = fdp.ConsumeRandomLengthString();
  std::vector<std::string> v;
  for (int i = 0; i < fdp.ConsumeIntegralInRange<int>(1, 1024); i++) {
    v.push_back(fdp.ConsumeRandomLengthString());
  }
  auto c = Combinator<std::string &>(s, v);
  auto it = c.begin();
  delete it;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzCombinator(data, size);
  return 0;
}