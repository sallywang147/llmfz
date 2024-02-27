#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "njs_parser.h"

extern "C" {
#include "njs_parser_import.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t parser_size = stream.ConsumeIntegral<size_t>();
  struct njs_parser_s* parser =
      static_cast<struct njs_parser_s*>(malloc(parser_size));
  if (parser == nullptr) {
    return 0;
  }

  const size_t token_size = stream.ConsumeIntegral<size_t>();
  struct njs_lexer_token_t* token =
      static_cast<struct njs_lexer_token_t*>(malloc(token_size));
  if (token == nullptr) {
    free(parser);
    return 0;
  }

  const size_t current_size = stream.ConsumeIntegral<size_t>();
  struct njs_queue_link_s* current =
      static_cast<struct njs_queue_link_s*>(malloc(current_size));
  if (current == nullptr) {
    free(parser);
    free(token);
    return 0;
  }

  const int result = njs_parser_import(parser, token, current);
  free(parser);
  free(token);
  free(current);
  return result;
}
```

The fixed code:

1. Includes the header file `njs_parser_import.h`.
2. Wraps the inclusion of the header file with `extern "C" {}`.

The build error is fixed.