#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "simdjson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the parsers
  simdjson::icelake::dom_parser_implementation icelake_parser;
  simdjson::fallback::dom_parser_implementation fallback_parser;
  simdjson::dom::document doc;

  // Consume the data as a string
  std::string json_string = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  icelake_parser.parse(&fallback_parser, (char*)json_string.data(), json_string.size(), &doc);

  return 0;
}