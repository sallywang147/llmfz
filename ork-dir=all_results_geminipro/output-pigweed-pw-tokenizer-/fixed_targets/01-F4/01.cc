#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "pw_tokenizer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  pw::tokenizer::NestedMessageDetokenizer detokenizer;
  while (stream.remaining_bytes() > 0) {
    const char next_char = stream.ConsumeIntegral<char>();
    detokenizer.next_char(next_char);
  }
  return 0;
}
```

The corrected code is shown above.

With this change, the code should build successfully.