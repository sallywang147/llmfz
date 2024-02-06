#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "iter/impl/combinator.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string
  std::string str = stream.ConsumeRandomLengthString();
  
  // Create a Combinator object
  iter::impl::Combinator<std::string&> combinator(str);
  
  // Create an Iterator object
  auto iterator = combinator.begin();
  
  // Call the destructor of Iterator
  iterator.~Iterator();

  return 0;
}