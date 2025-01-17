#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TidyDoc tdoc = tidyCreate();
  TidyBuffer tbuf = {0};
  
  tidyBufAttach(&tbuf, (byte *)data, size);

  tidySetInCharEncoding(tdoc, "raw");
  tidySetOutCharEncoding(tdoc, "raw");

  FILE *stream = fmemopen((void *)tbuf.bp, tbuf.size, "r");
  if (stream == NULL) {
    tidyBufDetach(&tbuf);
    tidyRelease(tdoc);
    return 0;
  }

  // Redirect stdin
  FILE *old_stdin = stdin;
  stdin = stream;

  tidyParseStdin(tdoc);

  // Restore stdin
  stdin = old_stdin;

  fclose(stream);
  tidyBufDetach(&tbuf);
  tidyRelease(tdoc);

  return 0;
}