#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char test_file[] = "libfuzzer.xml";

  FILE* fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 1;
  }

  char* buffer = (char*)malloc(size);
  if (!buffer) {
    XML_ParserFree(parser);
    return 1;
  }

  memcpy(buffer, data, size);

  XML_Parse(parser, buffer, size, 1);
  XML_ParserReset(parser, buffer);

  free(buffer);
  XML_ParserFree(parser);

  remove(test_file);
  return 0;
}