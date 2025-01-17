#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "simdjson.h"
#include "simdjson.cpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the parser
  simdjson::dom::parser parser;

  // Prepare the document
  simdjson::dom::document doc;

  // Parse the JSON document
  auto error = parser.parse(stream.ConsumeRemainingBytesAsString()).get(doc);

  // If parsing was successful, call stage2_next
  if (!error) {
    simdjson::fallback::dom_parser_implementation::stage2_next(&parser, &doc);
  }

  return 0;
}