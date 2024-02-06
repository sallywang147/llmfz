#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "simdjson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  simdjson::icelake::dom_parser_implementation icelake_parser;
  simdjson::fallback::dom_parser_implementation fallback_parser;
  simdjson::dom::document doc;

  // Consume the data as a string
  std::string json_string = provider.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  icelake_parser.parse(&fallback_parser, const_cast<char*>(json_string.c_str()), json_string.size(), &doc);

  return 0;
}