#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct usbredirparser* parser =
      usbredirparser_new(nullptr, nullptr, nullptr, nullptr, nullptr);
  if (parser == nullptr) {
    return 0;
  }
  usbredirparser_send_filter_reject(parser);
  usbredirparser_delete(parser);
  return 0;
}