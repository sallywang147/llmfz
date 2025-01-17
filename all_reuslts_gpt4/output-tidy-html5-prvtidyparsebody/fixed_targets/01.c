#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidy-int.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tidySetErrorBuffer(nullptr, nullptr);
    initialized = true;
  }

  FuzzedDataProvider stream(data, size);

  TidyDocImpl* doc = tidyCreateWithAllocator(nullptr);
  if (doc == nullptr) {
    return 0;
  }

  Node* body = tidyGetBody(doc);
  if (body == nullptr) {
    tidyRelease(doc);
    return 0;
  }

  int mode = stream.ConsumeIntegral<int>();

  prvTidyParseBody(doc, body, mode);

  tidyRelease(doc);

  return 0;
}