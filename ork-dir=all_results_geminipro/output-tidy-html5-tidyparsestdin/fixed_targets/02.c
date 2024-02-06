#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <tidy.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TidyDoc tdoc = tidyCreate();
  tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
  tidyOptSetBool(tdoc, TidyNumEntities, yes);
  tidyOptSetInt(tdoc, TidyWrapAsp, 0);
  tidyOptSetInt(tdoc, TidyWrapJste, 0);
  tidyOptSetInt(tdoc, TidyWrapPhp, 0);
  tidyOptSetInt(tdoc, TidyWrapScriptlets, 0);
  tidyOptSetInt(tdoc, TidyWrapSection, 0);
  tidyParseBuffer(tdoc, (const char *)data, size);
  tidyParseStdin(tdoc);  // Add this line to parse input from stdin
  tidyRelease(tdoc);
  return 0;
}