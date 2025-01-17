#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>
#include <exception>

#include "fuzzing/datasource/base.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::vector<std::string> vector_data;
  std::exception exception_data;

  // Consume data from the provider to populate the vector and exception.
  while (provider.remaining_bytes() > 0) {
    vector_data.push_back(provider.ConsumeRandomLengthString());
    try {
      throw std::runtime_error(provider.ConsumeRandomLengthString());
    } catch (const std::exception& e) {
      exception_data = e;
    }
  }

  // Call the target function.
  fuzzing::datasource::Base::Get<std::vector<std::string>>(vector_data, &exception_data, size);

  return 0;
}