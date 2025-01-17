#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "pcre2.h"

extern "C" {
#include "pcre2posix.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct pcre2_real_general_context_8* gcontext =
      pcre2_real_general_context_create_8(nullptr, nullptr);
  if (gcontext == nullptr) {
    return 0;
  }
  struct pcre2_real_convert_context_8* convert_context =
      pcre2_convert_context_create_8(gcontext);
  pcre2_real_general_context_free_8(gcontext);
  pcre2_convert_context_free_8(convert_context);
  return 0;
}
```

The original code has no build issues.