#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  TidyBuffer errbuf = {0};
  TidyDoc tdoc = tidyCreate();                     // Initialize "document"
  tidySetCharEncoding(tdoc, "raw");
  tidyOptSetBool(tdoc, TidyForceOutput, yes);      // Try harder
  tidyOptSetInt(tdoc, TidyWrapLen, 4096);
  tidySetErrorBuffer(tdoc, &errbuf);               // Capture diagnostics
  tidyBufInit(&errbuf);

  TidyBuffer docbuf = {0};
  tidyBufInit(&docbuf);
  tidyBufAttach(&docbuf, const_cast<uint8_t*>(data), size);

  TidyInputSource inbuf;
  tidyInitSource(&inbuf, &docbuf);

  int ret = tidyDocParseSource(tdoc, &inbuf);      // Parse the input
  if (ret >= 0) {
    ret = tidyCleanAndRepair(tdoc);               // Tidy it up!
  }
  if (ret >= 0) {
    ret = tidyRunDiagnostics(tdoc);               // Kvetch
  }
  if (ret >= 0) {
    ret = tidySaveStdout(tdoc);                   // Pretty Print
  }

  // Cleanup
  tidyBufFree(&docbuf);
  tidyBufFree(&errbuf);
  tidyRelease(tdoc);

  return 0;
}