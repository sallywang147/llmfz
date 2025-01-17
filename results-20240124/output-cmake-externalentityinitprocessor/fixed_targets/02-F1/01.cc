#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  XML_Parser parser = XML_ParserCreate(nullptr);
  if (!parser)
    return 0;

  char *open_entity_name = (char*)malloc(size + 1);
  if (!open_entity_name) {
    XML_ParserFree(parser);
    return 0;
  }
  memcpy(open_entity_name, data, size);
  open_entity_name[size] = '\0';

  char *base_url = (char*)malloc(size + 1);
  if (!base_url) {
    XML_ParserFree(parser);
    free(open_entity_name);
    return 0;
  }
  memcpy(base_url, data, size);
  base_url[size] = '\0';

  char *system_id = (char*)malloc(size + 1);
  if (!system_id) {
    XML_ParserFree(parser);
    free(open_entity_name);
    free(base_url);
    return 0;
  }
  memcpy(system_id, data, size);
  system_id[size] = '\0';

  char **ret = (char**)malloc(sizeof(char*));
  if (!ret) {
    XML_ParserFree(parser);
    free(open_entity_name);
    free(base_url);
    free(system_id);
    return 0;
  }

  int result = externalEntityInitProcessor(parser, open_entity_name, base_url, ret);
  XML_ParserFree(parser);
  free(open_entity_name);
  free(base_url);
  free(system_id);
  free(ret);

  return result;
}

int externalEntityInitProcessor(XML_Parser parser, const char *open_entity_name, const char *base_url, char **ret)
{
  return 0;
}