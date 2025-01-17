#include <cstddef>
#include <cstdint>
#include <string>

#include "FuzzUtils.h"
#include "NullBuffer.h"
#include "simdjson.h"

extern "C" {
#include "simdjson/dom/parser_implementation.h"
#include "simdjson/icelake/dom_parser_implementation.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzData fd(Data, Size);

  simdjson::fallback::dom_parser_implementation parser;
  simdjson::dom::document doc;
  simdjson_unused auto error = parser.stage1(doc, fd.data(), fd.size());
  if (error)
    return 0;

  simdjson_unused auto res = simdjson::icelake::dom_parser_implementation::stage2(&parser, &doc);
  return 0;
}