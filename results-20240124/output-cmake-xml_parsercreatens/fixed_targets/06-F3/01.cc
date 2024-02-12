#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "libxml/parser.h"

#ifdef __cplusplus
}
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  char ns[] = "http://www.example.com";
  struct XML_ParserStruct *parser = XML_ParserCreateNS(ns, ' ');
  if (!parser)
    return 0;

  XML_SetElementHandler(parser, start, end);
  XML_SetCharacterDataHandler(parser, cdata);
  XML_SetProcessingInstructionHandler(parser, pi);
  XML_SetCommentHandler(parser, comment);
  XML_SetExternalEntityRefHandler(parser, externalEntityRef);
  XML_SetUnknownEncodingHandler(parser, unknownEncoding);
  XML_SetStartNamespaceDeclHandler(parser, startNamespaceDecl);
  XML_SetEndNamespaceDeclHandler(parser, endNamespaceDecl);
  XML_SetNotationDeclHandler(parser, notationDecl);
  XML_SetUnparsedEntityDeclHandler(parser, unparsedEntityDecl);
  XML_SetEntityDeclHandler(parser, entityDecl);
  XML_SetXmlDeclHandler(parser, xmlDecl);
  XML_SetElementDeclHandler(parser, elementDecl);
  XML_SetAttlistDeclHandler(parser, attlistDecl);
  XML_SetStartCdataSectionHandler(parser, startCdataSection);
  XML_SetEndCdataSectionHandler(parser, endCdataSection);
  XML_SetDefaultHandler(parser, defaultHandler);
  XML_SetDoctypeDeclHandler(parser, doctypeDecl);
  XML_SetXmlNsHandler(parser, xmlNs);
  XML_SetXmlSaxHandler(parser, xmlSax);

  if (XML_Parse(parser, (char*)data, size, 1) == XML_STATUS_ERROR) {
    fprintf(stderr, "%s at line %d\n", XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
    XML_ParserFree(parser);
    return 0;
  }

  XML_ParserFree(parser);
  return 0;
}