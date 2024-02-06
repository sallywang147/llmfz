#include "tidy.h"
#include "tidybuffio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
#include <tidy/tidy.h>
}

int tidyDocParseSource(struct _TidyDocImpl * doc, struct _TidyInputSource * source) {
  uint8_t decider;

  // We need enough data for picking all of the options. One byte per option.
  if (source->nextByte < 5) {
    return 0;
  }

  // Decide output format
  decider = source->nextByte;
  source->nextByte++;
  if (decider % 3 == 0)
    tidyOptSetBool(doc, TidyXhtmlOut, yes);
  else {
    tidyOptSetBool(doc, TidyXhtmlOut, no);
  }

  if (decider % 3 == 1)
    tidyOptSetBool(doc, TidyHtmlOut, yes);
  else {
    tidyOptSetBool(doc, TidyHtmlOut, no);
  }

  if (decider % 3 == 2)
    tidyOptSetBool(doc, TidyXmlOut, yes);
  else {
    tidyOptSetBool(doc, TidyXmlOut, no);
  }

  // Set an error buffer.
  tidySetErrorBuffer(doc, source->errbuf);

  // Parse the data
  decider = source->nextByte;
  source->nextByte++;
  switch (decider % 2) {
  case 0: {
    char filename[256];
    sprintf(filename, "/tmp/libfuzzer.%d", getpid());

    FILE *fp = fopen(filename, "wb");
    if (!fp) {
      return 0;
    }
    fwrite(source->nextByte, source->size - source->nextByte, 1, fp);
    fclose(fp);

    source->source = filename;
    source->size = strlen(filename);
  } break;
  case 1: {
    char *inp = malloc(source->size - source->nextByte + 1);
    inp[source->size - source->nextByte] = '\0';
    memcpy(inp, source->nextByte, source->size - source->nextByte);
    source->source = inp;
    source->size = strlen(inp);
  }
  }

  // Cleanup
  return tidyDocParseSource(doc, source);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TidyDoc tdoc = tidyCreate();
  TidyBuffer fuzz_toutput;
  TidyBuffer fuzz_terror;

  tidyBufInit(&fuzz_toutput);
  tidyBufInit(&fuzz_terror);

  struct _TidyInputSource source;
  source.nextByte = data;
  source.size = size;
  source.errbuf = &fuzz_terror;

  tidyDocParseSource(tdoc, &source);

  tidyBufFree(&fuzz_toutput);
  tidyBufFree(&fuzz_terror);

  tidyRelease(tdoc);

  return 0;
}