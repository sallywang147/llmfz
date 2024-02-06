#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expat.h"

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char test_file[] = "libfuzzer.xml";

  FILE *fp = fopen(test_file, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  XML_Parser parser = XML_ParserCreate(NULL);
  XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor2);
  if (!XML_ParseFile(parser, test_file)) {
    return 1;
  }

  remove(test_file);
  return 0;
}

extern "C" int externalEntityInitProcessor2(XML_Parser parser, const XML_Char *context, const XML_Char *base, const XML_Char *systemId, const XML_Char *publicId) {
  return XML_STATUS_ERROR;
}