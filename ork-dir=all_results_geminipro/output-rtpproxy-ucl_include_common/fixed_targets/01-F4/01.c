#include <fuzzer/FuzzedDataProvider.h>

#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "ucl.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  size_t len = provider.ConsumeIntegralInRange<size_t>(0, size);
  char *data_copy = new char[len + 1];
  provider.ConsumeBytes(data_copy, len);
  data_copy[len] = '\0';

  struct ucl_parser *parser = ucl_parser_new(0);
  struct ucl_object *obj = ucl_parser_parse(parser, data_copy);
  if (obj == NULL) {
    ucl_parser_free(parser);
    delete[] data_copy;
    return 0;
  }
  ucl_parser_free(parser);

  bool default_try = provider.ConsumeBool();
  bool default_sign = provider.ConsumeBool();

  bool result = ucl_include_common(data_copy, len, obj, NULL, default_try, default_sign);

  ucl_object_unref(obj);
  delete[] data_copy;

  return 0;
}
```

The issue is that the header file `ucl.h` is not wrapped with `extern "C" {}`. This is necessary because the C++ compiler uses name mangling, which can cause issues when linking with C code. By wrapping the header file with `extern "C" {}`, we tell the compiler to not mangle the names of the functions and variables in the header file, which allows the linker to find them correctly.