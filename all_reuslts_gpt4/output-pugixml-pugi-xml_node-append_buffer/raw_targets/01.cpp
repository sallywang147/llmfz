#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pugixml.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  pugi::xml_document doc;
  pugi::xml_parse_result result;
  pugi::xml_node node = doc.append_child("node");

  // Extract integral values
  size_t options = stream.ConsumeIntegral<size_t>();
  int encoding = stream.ConsumeIntegral<int>();
  int depth = stream.ConsumeIntegral<int>();

  // Extract a string
  std::string buffer = stream.ConsumeRemainingBytesAsString();
  
  // Call the function to fuzz
  node.append_buffer(&result, &node, buffer.c_str(), options, encoding, depth);

  return 0;
}