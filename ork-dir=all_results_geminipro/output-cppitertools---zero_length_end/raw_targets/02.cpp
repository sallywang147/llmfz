#include <fuzzer/FuzzedDataProvider.h>

#include <iterator>
#include <string>
#include <vector>

using iter::Combinator;

void FuzzCombinator(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string s = fdp.ConsumeRandomLengthString();
  std::vector<std::string> v;
  for (auto &&c : Combinator<std::string &>(s)) {
    v.emplace_back(std::begin(c), std::end(c));
  }
  auto c = Combinator<std::string &>(s);
  Combinator<std::string &>::Iterator<std::string &> *container = &c;
  std::string *str = &s;
  iter::impl::Combinator<std::string &>::Iterator<std::string &>::zero_length_end(
      container, str);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzCombinator(data, size);
  return 0;
}