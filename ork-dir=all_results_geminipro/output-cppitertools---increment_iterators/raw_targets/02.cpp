#include <chain.hpp>
#include <combinations.hpp>
#include <compress.hpp>
#include <cycle.hpp>
#include <groupby.hpp>

#include <fuzzer/FuzzedDataProvider.h>

#include <iterator>
#include <string>
#include <utility>
#include <vector>

using iter::chain;
using iter::combinations;
using iter::compress;
using iter::cycle;
using iter::groupby;

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
  auto c = compress(v, b);
  iter::impl::Compressed<std::vector<int> &, std::vector<bool> &>::Iterator<std::vector<int> &, std::vector<bool> &> it(c);
  iter::impl::Compressed<std::vector<int> &, std::vector<bool> &>::Iterator<std::vector<int> &, std::vector<bool> &> *it_ptr = &it;
  it.increment_iterators(it_ptr);
  return 0;
}