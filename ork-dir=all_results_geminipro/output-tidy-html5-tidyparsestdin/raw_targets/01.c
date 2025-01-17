#include "tidy.h"
#include "tidybuffio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int tidyParseStdin(struct _TidyDoc *tdoc) {
  uint8_t decider;

  TidyBuffer fuzz_tinput;
  tidyBufInit(&fuzz_tinput);

  decider = **data;
  *data += 1;
  *size -= 1;
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

  tidyBufFree(&fuzz_tinput);

  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TidyDoc tdoc = tidyCreate();

  tidyParseStdin(tdoc);

  tidyRelease(tdoc);

  return 0;
}