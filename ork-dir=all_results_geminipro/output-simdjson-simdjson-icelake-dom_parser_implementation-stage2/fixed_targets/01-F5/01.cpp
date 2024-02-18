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

#define simdjson_unused static inline

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzData fd(Data, Size);

  simdjson::fallback::dom_parser_implementation parser;
  simdjson::dom::document doc;
  simdjson_unused auto error = parser.stage1(fd.data(), fd.size(), &doc); // Corrected the call to stage1
  if (error)
    return 0;

  simdjson_unused auto res = simdjson::icelake::dom_parser_implementation::stage2(&parser, &doc); // Corrected the call to stage2
  return 0;
}