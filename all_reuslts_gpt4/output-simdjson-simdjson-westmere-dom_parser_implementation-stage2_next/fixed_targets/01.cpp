#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "simdjson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  simdjson::dom::parser parser;
  simdjson::dom::document doc;
  simdjson::fallback::dom_parser_implementation fallback_parser;
  simdjson::westmere::dom_parser_implementation westmere_parser;

  // Consume data as string
  std::string json = fuzzed_data.ConsumeRemainingBytesAsString();

  // Parse JSON and get document
  simdjson::error_code error = parser.parse(json).get(doc);
  if (error) {
    return 0;
  }

  // Call the function to fuzz
  westmere_parser.stage2_next(&fallback_parser, &doc);

  return 0;
}