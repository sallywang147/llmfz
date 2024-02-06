#include <cstddef>
#include <cstdint>
#include <string>

#include "simdjson.h"
#include "FuzzUtils.h"
#include "NullBuffer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzData fd(Data, Size);
  const int action = fd.getInt<0, 31>();

  // there will be some templatized functions like is() which need to be tested
  // on a type. select one dynamically and create a function that will invoke
  // with that type
  const int selecttype = fd.getInt<0, 7>();
  auto invoke_with_type = [selecttype](auto cb) {
    using constcharstar = const char *;
    switch (selecttype) {
    case 0:
      cb(bool{});
      break;
    case 1:
      cb(double{});
      break;
    case 2:
      cb(uint64_t{});
      break;
    case 3:
      cb(int64_t{});
      break;
    case 4:
      cb(std::string_view{});
      break;
    case 5:
      cb(constcharstar{});
      break;
    case 6:
      cb(simdjson::dom::array{});
      break;
    case 7:
      cb(simdjson::dom::object{});
      break;
    }
  };

  const auto index = fd.get<size_t>();

  // split the remainder of the document into strings
  auto strings = fd.splitIntoStrings();
  while (strings.size() < 2) {
    strings.emplace_back();
  }
  const auto str = strings[0];

  // exit if there was too little data
  if (!fd)
    return 0;

  simdjson::dom::parser parser;
  simdjson_unused simdjson::dom::element elem;
  simdjson_unused auto error = parser.parse(strings[1]).get(elem);

  if (error)
    return 0;

  simdjson::fallback::dom_parser_implementation fallback_parser;
  simdjson::dom::document doc;
  simdjson_unused simdjson::dom::element elem_fallback;

  // Call stage1_parse before stage2_next
  simdjson_unused auto error_fallback = fallback_parser.stage1_parse(str, &doc, &elem_fallback);

  if (error_fallback)
    return 0;

  switch (action) {
  case 0: {
    simdjson_unused auto v = fallback_parser.stage2_next(&doc);
    break;
  }
  }

  return 0;
}