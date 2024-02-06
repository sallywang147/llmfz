#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include "iter/impl/combinator.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  iter::impl::Combinator<std::string&> combinator(str);
  iter::impl::Combinator<std::string&>::Iterator iterator = combinator.begin();

  iterator.zero_length_end(&iterator, &str);

  return 0;
}