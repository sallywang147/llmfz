 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmlparse.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char *test_file = (char*) malloc(size + 1);
  memcpy(test_file, data, size);
  test_file[size] = 0;

  char *test_file_ptr = test_file;
  char *test_file_end = test_file + size;

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser)
    return 0;

  XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor2);
  while (test_file_ptr < test_file_end) {
    int done;
    int len = test_file_end - test_file_ptr;
    if (len > 1024)
      len = 1024;
    XML_Parse(parser, test_file_ptr, len, 0, &done);
    test_file_ptr += len;
    if (done)
      break;
  }

  XML_ParserFree(parser);
  free(test_file);
  return 0;
}