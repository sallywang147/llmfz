#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <exception>

#include "fuzzing/datasource/base.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::vector<std::string> this_vector;
  std::exception id;
  size_t some_size = stream.ConsumeIntegral<size_t>();

  // Call the function
  fuzzing::datasource::Base::Get<std::vector<std::string>>(&this_vector, &id, some_size);

  return 0;
}