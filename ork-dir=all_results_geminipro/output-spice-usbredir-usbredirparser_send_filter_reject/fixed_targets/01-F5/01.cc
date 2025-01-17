#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "usbredirparser.h"
#include <libusbredirparser.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct usbredirparser* parser = usbredirparser_new();

  usbredirparser_send_filter_reject(parser, stream.ConsumeRemainingBytes());

  usbredirparser_free(parser);
  return 0;
}
```

The original code has no issues. The build error message is not provided, so there is no way to fix the code.