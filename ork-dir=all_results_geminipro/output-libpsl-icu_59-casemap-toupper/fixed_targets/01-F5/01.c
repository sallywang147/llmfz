#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace icu;

extern "C" {
#include "unicode/casemap.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    Locale::setDefault(Locale::getUS());
    initialized = true;
  }
  CaseMap* case_map = CaseMap::createUpper();
  if (case_map == nullptr) {
    return 0;
  }

  std::vector<uint16_t> input_buffer;
  std::vector<uint16_t> output_buffer(size);
  FuzzedDataProvider provider(data, size);
  // Initially, start by feeding the decoder more data.
  while (provider.remaining_bytes() != 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<uint8_t>(next_size);
    for (size_t i = 0; i < next_input.size(); ++i) {
      input_buffer.push_back(next_input[i]);
    }
  }

  Edits edits;
  int32_t error_code = 0;
  case_map->toUpper("", 0, input_buffer.data(), input_buffer.size(),
                    output_buffer.data(), output_buffer.size(), &edits,
                    &error_code);
  delete case_map;

  return 0;
}