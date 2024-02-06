#include <fuzzer/FuzzedDataProvider.h>

#include <string>
#include <vector>

#include "combinator.hpp"

using iter::Combinator;

extern "C" {

void FuzzCombinator(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string s = fdp.ConsumeRandomLengthString();
  auto c = Combinator<std::string &>(s);
  auto it = c.begin();
  it.zero_length_end(&it, &s);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzCombinator(data, size);
  return 0;
}

} // extern "C"