#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  TidyBuffer buffer = {0};
  tidyBufAttach(&buffer, const_cast<uint8_t*>(data), size);

  TidyInputSource input_source;
  if (tidyInitSource(&input_source, &buffer, nullptr, nullptr) != 0) {
    tidyBufDetach(&buffer);
    return 0;
  }

  TidyDoc tdoc = tidyCreate();
  tidyParseSource(tdoc, &input_source);

  tidyRelease(tdoc);
  tidyBufDetach(&buffer);

  return 0;
}