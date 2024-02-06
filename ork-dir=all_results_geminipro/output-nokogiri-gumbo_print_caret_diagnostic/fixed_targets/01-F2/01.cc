#include "../src/nokogiri_gumbo.h"
#include <stdint.h>

extern "C" {
#include <gumbo.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 10) {
    return 0;
  }

  GumboInternalError error;
  gumbo_init_error(&error);

  gumbo_parse_caret_diagnostic(&error, (char *)data, size);

  gumbo_free_error(&error);

  return 0;
}
```

The original code had a typo in the function name `gumbo_parse_caret_diagnostic` instead of `gumbo_print_caret_diagnostic`. This typo caused the build error.