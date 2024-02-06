#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct usbredirparser* parser = usbredirparser_create();
  if (parser == nullptr) {
    return 0;
  }

  usbredirparser_send_filter_reject(parser);

  usbredirparser_destroy(parser);

  return 0;
}