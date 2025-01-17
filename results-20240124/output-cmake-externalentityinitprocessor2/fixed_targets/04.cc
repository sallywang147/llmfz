#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "expat.h"

extern "C" {
#include "expat.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  XML_Parser parser = XML_ParserCreate(nullptr);
  XML_SetParamEntityParsing(parser, XML_PARAM_ENTITY_PARSING_ALWAYS);

  char* buf = static_cast<char*>(malloc(size));
  memcpy(buf, data, size);

  int ret = XML_ExternalEntityInitParser(parser, buf, buf + size, nullptr);
  XML_ParserFree(parser);
  free(buf);

  return ret;
}

extern "C" int externalEntityInitProcessor2(XML_Parser parser, const char *context, const char *base, const char **systemId, const char **publicId)
{
  return XML_STATUS_ERROR;
}