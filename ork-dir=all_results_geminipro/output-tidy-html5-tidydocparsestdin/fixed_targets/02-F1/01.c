#include "tidy.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TidyDoc tdoc = tidyCreate();
  tidyOptSetBool(tdoc, TidyQuiet, yes);
  tidyOptSetBool(tdoc, TidyShowWarnings, no);
  tidyOptSetBool(tdoc, TidyNumEntities, yes);
  tidyOptSetBool(tdoc, TidyFixUri, yes);
  tidyOptSetBool(tdoc, TidyMakeBare, yes);
  tidyOptSetBool(tdoc, TidyWrapAsp, yes);
  tidyOptSetBool(tdoc, TidyWrapJste, yes);
  tidyOptSetBool(tdoc, TidyWrapPhp, yes);
  tidyOptSetBool(tdoc, TidyWrapScriptlets, yes);
  tidyOptSetBool(tdoc, TidyWrapSection, yes);

  tidyParseStdin(tdoc); // Call tidyParseStdin() here
  tidyRelease(tdoc);

  return 0;
}