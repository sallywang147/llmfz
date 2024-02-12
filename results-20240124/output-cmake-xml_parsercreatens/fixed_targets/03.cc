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

  XML_Parser parser = XML_ParserCreateNS(nullptr, ' ');
  if (!parser) {
    return 1;
  }

  remove(test_file);
  return 0;
}