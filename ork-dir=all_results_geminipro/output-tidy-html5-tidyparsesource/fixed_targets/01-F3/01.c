The build error message indicates that the `tidy` library functions are not being properly linked to the program. To fix this, the `#include` directives for the `tidy` library need to be wrapped with `extern "C" {}`.

The corrected code:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "tidy.h"
#include "tidybuffio.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    tidyInit();
    initialized = true;
  }
  TidyDoc tdoc = tidyCreate();
  TidyBuffer fuzz_toutput;
  TidyBuffer fuzz_terror;

  tidyBufInit(&fuzz_toutput);
  tidyBufInit(&fuzz_terror);

  tidySetErrorBuffer(tdoc, &fuzz_terror);
  tidySetOutputBuffer(tdoc, &fuzz_toutput);

  TidyInputSource source;
  source.encoding = NULL;
  source.flags = 0;
  source.lastByte = 0;
  source.line = 1;
  source.column = 1;
  source.charEncoding = CharEncoding_UTF8;
  source.nextByte = data;
  source.bytesLeft = size;

  int ret = tidyParseSource(tdoc, &source);

  tidyBufFree(&fuzz_toutput);
  tidyBufFree(&fuzz_terror);
  tidyRelease(tdoc);

  return 0;
}