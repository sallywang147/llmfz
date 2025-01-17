#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <simdjson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  simdjson::icelake::dom_parser_implementation icelake_parser;
  simdjson::fallback::dom_parser_implementation fallback_parser;
  simdjson::dom::document doc;

  FuzzedDataProvider stream(data, size);
  std::string json = stream.ConsumeRemainingBytesAsString();

  if (fallback_parser.parse(json).error()) {
    return 0;
  }

  icelake_parser.stage2(&fallback_parser, &doc);

  return 0;
}