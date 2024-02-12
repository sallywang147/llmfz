 #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char* xml_data = (char*)malloc(size + 1);
  memcpy(xml_data, data, size);
  xml_data[size] = '\0';

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    free(xml_data);
    return 0;
  }

  XML_SetElementHandler(parser, NULL, NULL);
  XML_SetCharacterDataHandler(parser, NULL);
  XML_SetExternalEntityRefHandler(parser, externalEntityInitProcessor);
  XML_SetExternalEntityRefHandlerArg(parser, NULL);
  XML_SetNamespaceDeclHandler(parser, NULL, NULL);
  XML_SetUnparsedEntityDeclHandler(parser, NULL, NULL);
  XML_SetNotationDeclHandler(parser, NULL, NULL);
  XML_SetAttlistDeclHandler(parser, NULL);
  XML_SetStartDoctypeDeclHandler(parser, NULL);
  XML_SetEndDoctypeDeclHandler(parser, NULL);
  XML_SetProcessingInstructionHandler(parser, NULL);
  XML_SetCommentHandler(parser, NULL);
  XML_SetStartCdataSectionHandler(parser, NULL);
  XML_SetEndCdataSectionHandler(parser, NULL);
  XML_SetDefaultHandler(parser, NULL);
  XML_SetDefaultHandlerExpand(parser, NULL);
  XML_SetNotStandaloneHandler(parser, NULL);
  XML_SetUnknownEncodingHandler(parser, NULL, NULL);
  XML_SetElementDeclHandler(parser, NULL, NULL);
  XML_SetAttlistDeclHandlerArg(parser, NULL);
  XML_SetEntityDeclHandler(parser, NULL, NULL);
  XML_SetXmlDeclHandler(parser, NULL, NULL);
  XML_SetXmlNsHandler(parser, NULL, NULL);
  XML_SetParamEntityParsing(parser, XML_PARAM_ENTITY_PARSING_NEVER);
  XML_UseParserAsHandlerArg(parser);

  int ret = XML_Parse(parser, xml_data, size, 1);
  if (!ret) {
    fprintf(stderr, "XML parsing error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
  }

  XML_ParserFree(parser);
  free(xml_data);

  return 0;
}