#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <libxml/parser.h>

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

  XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor2);

  if (!XML_ParseFile(parser, test_file)) {
    return 1;
  }

  remove(test_file);
  return 0;
}