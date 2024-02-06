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

void FuzzChained(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::vector<char> v;
  for (int i = 0; i < fdp.ConsumeIntegralInRange<int>(1, 1024); i++) {
    v.push_back((char)fdp.ConsumeIntegral<char>());
  }
  const auto ch = chain(v, v, v);
  std::vector<char> v2(std::begin(ch), std::end(ch));
}

int length(const std::string &s) { return s.size(); }

void FuzzGroupby(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::vector<std::string> v;
  for (int i = 0; i < fdp.ConsumeIntegralInRange<int>(1, 1024); i++) {
    v.push_back(fdp.ConsumeRandomLengthString());
  }
  for (auto &&gb : groupby(v, length)) {
  }
}

void FuzzCycle(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::vector<int> v;
  for (int i = 0; i < fdp.ConsumeIntegralInRange<int>(1, 1024); i++) {
    v.push_back(fdp.ConsumeIntegral<int>());
  }
  auto ch = cycle(v);

  std::vector<int> o;
  size_t count = 0;
  for (auto val : ch) {
    o.push_back(val);
    count++;
    if (count > 1500) {
      break;
    }
  }
}

void FuzzCombinations(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string s = fdp.ConsumeRandomLengthString();
  std::vector<std::vector<char>> sc;
  size_t count = 0;
  for (auto &&v : combinations(s, fdp.ConsumeIntegralInRange(1, 16))) {
    sc.emplace_back(std::begin(v), std::end(v));
    count++;
    if (count > 1500) {
      break;
    }
  }
}

void FuzzCompress(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::vector<int> ivec;
  std::vector<bool> bvec;
  for (int i = 0; i < 100; i++) {
    ivec.push_back(fdp.ConsumeIntegralInRange(1, 1000000));
    ivec.push_back(fdp.ConsumeBool());
  }
  auto c = compress(ivec, bvec);
  std::vector<int> v(std::begin(c), std::end(c));
  const auto &c2 = c;
  (void)(std::begin(c) == std::end(c2));
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzChained(data, size);
  FuzzGroupby(data, size);
  FuzzCycle(data, size);
  FuzzCombinations(data, size);
  FuzzCompress(data, size);

  // Fuzz iter::impl::Compressed<std::vector<int> &, std::vector<bool> &>::Iterator<std::__1::vector<int, std::__1::allocator<int> >&, std::__1::vector<bool, std::__1::allocator<bool> >&>::operator++
  {
    FuzzedDataProvider fdp(data, size);
    std::vector<int> ivec;
    std::vector<bool> bvec;
    for (int i = 0; i < 100; i++) {
      ivec.push_back(fdp.ConsumeIntegralInRange(1, 1000000));
      ivec.push_back(fdp.ConsumeBool());
    }
    auto c = compress(ivec, bvec);
    auto it = c.begin();
    iter::impl::Compressed<std::vector<int> &, std::vector<bool> &>::Iterator<std::__1::vector<int, std::__1::allocator<int> >&, std::__1::vector<bool, std::__1::allocator<bool> >&>::operator++(it);
  }

  return 0;
}