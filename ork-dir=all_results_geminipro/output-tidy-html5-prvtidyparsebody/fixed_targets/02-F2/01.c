#include <tidy.h>
#include <tidybuffio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
#include <tidy.h>
#include <tidybuffio.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  uint8_t decider;

  // We need enough data for picking all of the options. One byte per option.
  if (size < 5) {
    return 0;
  }

  TidyDoc tdoc = tidyCreate();

  // Decide output format
  decider = *data;
  data++;
  size--;
  if (decider % 3 == 0)
    tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
  else {
    tidyOptSetBool(tdoc, TidyXhtmlOut, no);
  }

  if (decider % 3 == 1)
    tidyOptSetBool(tdoc, TidyHtmlOut, yes);
  else {
    tidyOptSetBool(tdoc, TidyHtmlOut, no);
  }

  if (decider % 3 == 2)
    tidyOptSetBool(tdoc, TidyXmlOut, yes);
  else {
    tidyOptSetBool(tdoc, TidyXmlOut, no);
  }

  // Set an error buffer.
  TidyBuffer fuzz_terror;
  tidyBufInit(&fuzz_terror);
  tidySetErrorBuffer(tdoc, &fuzz_terror);

  // Parse the data
  decider = *data;
  data++;
  size--;
  switch (decider % 2) {
  case 0: {
    char filename[256];
    sprintf(filename, "/tmp/libfuzzer.%d", getpid());

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
      return 0;
    }
    fwrite(data, size, 1, fp);
    fclose(fp);

    tidyParseFile(tdoc, filename);
    unlink(filename);
  } break;
  case 1: {
    char *inp = malloc(size + 1);
    inp[size] = '\0';
    memcpy(inp, data, size);
    tidyParseString(tdoc, inp);
    free(inp);
  }
  }

  // Cleanup
  tidyBufFree(&fuzz_terror);
  tidyRelease(tdoc);

  return 0;
}