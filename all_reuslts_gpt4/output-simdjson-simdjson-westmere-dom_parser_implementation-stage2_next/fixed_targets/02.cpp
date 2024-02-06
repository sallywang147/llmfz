#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "simdjson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  simdjson::dom::parser parser;
  simdjson::dom::document doc;
  simdjson::fallback::dom_parser_implementation fallback_parser;
  simdjson::westmere::dom_parser_implementation westmere_parser;

  // Extract a string
  std::string json = stream.ConsumeRemainingBytesAsString();
  
  // Parse the JSON to a document
  auto error = parser.parse(json).get(doc);
  if (error) {
    return 0;
  }

  // Call the target function
  westmere_parser.stage2_next(&fallback_parser, &doc);

  return 0;
}