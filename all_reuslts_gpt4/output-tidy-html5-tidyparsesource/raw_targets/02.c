#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  TidyBuffer buf = {0};
  tidyBufAttach(&buf, const_cast<uint8_t*>(data), size);

  TidyInputSource in = {0};
  tidyInitInputSource(&in, &buf, nullptr);

  TidyDoc tdoc = tidyCreate();
  tidyParseSource(tdoc, &in);

  tidyBufDetach(&buf);
  tidyRelease(tdoc);

  return 0;
}