#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tidyInit();
    initialized = true;
  }
  TidyDoc doc = tidyCreate();
  TidyBuffer input_buffer = {0};
  tidyBufInit(&input_buffer);
  tidyBufAppend(&input_buffer, data, size);
  TidyInputSource source = {0};
  tidyParseSource(doc, &source, &input_buffer); // Function call added
  tidyBufFree(&input_buffer);
  tidyRelease(doc);
  return 0;
}