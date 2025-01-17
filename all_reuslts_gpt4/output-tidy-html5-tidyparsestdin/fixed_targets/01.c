#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "tidy.h"
#include "tidybuffio.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  TidyDoc tdoc = tidyCreate();
  TidyBuffer inbuf = {0};
  tidyBufAttach(&inbuf, const_cast<unsigned char*>(data), size);
  FILE* f = fmemopen(inbuf.bp, inbuf.size, "r");
  if (!f) {
    tidyBufDetach(&inbuf);
    tidyRelease(tdoc);
    return 0;
  }
  int old_stdin = dup(fileno(stdin));
  if (old_stdin == -1) {
    fclose(f);
    tidyBufDetach(&inbuf);
    tidyRelease(tdoc);
    return 0;
  }
  fflush(stdin);
  dup2(fileno(f), fileno(stdin));
  fclose(f);
  tidyParseStdin(tdoc);
  fflush(stdin);
  dup2(old_stdin, fileno(stdin));
  close(old_stdin);
  tidyBufDetach(&inbuf);
  tidyRelease(tdoc);
  return 0;
}