#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pugixml.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  pugi::xml_parse_result parse_result;
  pugi::xml_node node;
  
  // Consume some bytes for the buffer to append
  const size_t buffer_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  auto buffer = provider.ConsumeBytes<char>(buffer_size);
  
  // Consume remaining bytes for options and encoding
  size_t options = provider.ConsumeIntegral<size_t>();
  int encoding = provider.ConsumeIntegral<int>();

  // Call the function to fuzz
  node.append_buffer(&parse_result, &node, buffer.data(), options, encoding, 0);

  return 0;
}