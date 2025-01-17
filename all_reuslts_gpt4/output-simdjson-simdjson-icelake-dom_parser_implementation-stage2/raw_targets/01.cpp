#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "simdjson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  simdjson::dom::parser parser;
  simdjson::dom::document doc;
  simdjson::fallback::dom_parser_implementation fallback;
  simdjson::icelake::dom_parser_implementation icelake;

  // Consume bytes as a string
  std::string jsonString = stream.ConsumeRemainingBytesAsString();

  // Parse the string to a document
  simdjson::error_code error = parser.parse(jsonString).get(doc);
  if (error) {
    return 0;
  }

  // Call the function to fuzz
  icelake.stage2(&fallback, &doc);

  return 0;
}