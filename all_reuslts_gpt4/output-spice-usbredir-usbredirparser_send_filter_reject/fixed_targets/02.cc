#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a usbredirparser
  struct usbredirparser* parser = usbredirparser_create();

  // Send filter reject
  usbredirparser_send_filter_reject(parser);

  // Clean up
  usbredirparser_destroy(parser);

  return 0;
}