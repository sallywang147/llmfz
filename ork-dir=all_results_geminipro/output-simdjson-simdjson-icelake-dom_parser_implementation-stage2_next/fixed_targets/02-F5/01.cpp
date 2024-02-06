#include <cstddef>
#include <cstdint>
#include <string>

#include "FuzzUtils.h"
#include "NullBuffer.h"

extern "C" {
#include "simdjson.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzData fd(Data, Size);

  // exit if there was too little data
  if (!fd)
    return 0;

  simdjson::dom::parser parser;
  simdjson_unused simdjson::dom::element elem;
  simdjson_unused auto error = parser.parse(fd.data()).get(elem);

  if (error)
    return 0;

  auto doc = fd.get<simdjson::dom::document *>();
  auto impl = fd.get<simdjson::fallback::dom_parser_implementation *>();
  simdjson_unused auto v = impl->stage2_next(doc);
  return 0;
}
```

The issue was that the `simdjson` header was not wrapped with `extern "C" {}`. This is necessary because the `simdjson` header is written in C++, and the `LLVMFuzzerTestOneInput` function is written in C. Without the `extern "C" {}` wrapper, the linker would not be able to find the `simdjson` symbols.