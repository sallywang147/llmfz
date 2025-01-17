#include "tidy.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int tidyDocParseStdin(struct _TidyDocImpl *doc) {
  TidyBuffer output = {0};
  TidyBuffer errbuf = {0};
  int rc = tidyParseStdin(doc);
  tidyBufFree(&output);
  tidyBufFree(&errbuf);
  return rc;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TidyDoc tdoc = tidyCreate();
  tidyOptSetBool(tdoc, TidyQuiet, yes);
  tidyDocParseStdin(tdoc);
  tidyRelease(tdoc);
  return 0;
}