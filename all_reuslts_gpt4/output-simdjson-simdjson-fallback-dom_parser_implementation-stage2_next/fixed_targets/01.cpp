#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "simdjson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  simdjson::dom::parser parser;
  simdjson::dom::document doc;
  simdjson::fallback::dom_parser_implementation fallback_parser;

  // Consume data as a string and try to parse it
  std::string json = stream.ConsumeRemainingBytesAsString();
  auto error = parser.parse(json).get(doc);
  if (error) {
    return 0;
  }

  // Call the function to fuzz
  simdjson::fallback::dom_parser_implementation::stage2_next(&fallback_parser, &doc);

  return 0;
}