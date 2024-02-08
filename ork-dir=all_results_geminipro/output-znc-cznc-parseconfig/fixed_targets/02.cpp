#include <stdint.h>
#include <znc/znc.h>

extern "C" {
#include <string>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  CZNC znc;
  znc.ParseConfig(input);
  return 0;
}
```

The original code has no issues.