#include "fuzz.h"

#include <libxml/catalog.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlerror.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlsave.h>
#include <libxml/xmlschemas.h>

int LLVMFuzzerInitialize(int *argc ATTRIBUTE_UNUSED, char ***argv ATTRIBUTE_UNUSED) {
  xmlFuzzMemSetup();
  xmlInitParser();
#ifdef LIBXML_CATALOG_ENABLED
  xmlInitializeCatalog();
  xmlCatalogSetDefaults(XML_CATA_ALLOW_NONE);
#endif
  xmlSetGenericErrorFunc(NULL, xmlFuzzErrorFunc);
  xmlSetExternalEntityLoader(xmlFuzzEntityLoader);

  return 0;
}

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlParserCtxtPtr ctxt;
  xmlDocPtr doc;
  const char *docBuffer, *docUrl, *xsdBuffer;
  size_t maxAlloc, docSize, xsdSize;
  int opts;

  xmlFuzzDataInit(data, size);
  opts = (int)xmlFuzzReadInt(4);
  /*
   * Disable options that are known to cause timeouts
   */
  opts &= ~XML_PARSE_XINCLUDE & ~XML_PARSE_DTDVALID & ~XML_PARSE_SAX1;
  maxAlloc = xmlFuzzReadInt(4) % (size + 100);

  xmlFuzzReadEntities();
  docBuffer = xmlFuzzMainEntity(&docSize);
  docUrl = xmlFuzzMainUrl();
  if (docBuffer == NULL)
    goto exit;

  xsdBuffer = xmlFuzzXSD(&xsdSize);
  if (xsdBuffer == NULL)
    goto exit;

  /* Pull parser */

  xmlFuzzMemSetLimit(maxAlloc);
  ctxt = xmlNewParserCtxt();
  if (ctxt != NULL) {
    doc = xmlCtxtReadMemory(ctxt, docBuffer, docSize, docUrl, NULL, opts);
    xmlFuzzCheckMallocFailure("xmlCtxtReadMemory", ctxt->errNo == XML_ERR_NO_MEMORY);

    if (doc != NULL) {
      xmlSchemaParserCtxtPtr schemaCtxt;
      xmlSchemaValidCtxtPtr validCtxt;
      int ret;

      schemaCtxt = xmlSchemaNewParserCtxt(xsdBuffer, xsdSize);
      xmlFuzzCheckMallocFailure("xmlSchemaNewParserCtxt", schemaCtxt == NULL);

      validCtxt = xmlSchemaNewValidCtxt(schemaCtxt);
      xmlFuzzCheckMallocFailure("xmlSchemaNewValidCtxt", validCtxt == NULL);

      ret = xmlTextReaderSchemaValidateInternal(doc->reader, NULL, validCtxt, opts);
      xmlFuzzCheckMallocFailure("xmlTextReaderSchemaValidateInternal", ret == -1);

      xmlSchemaFreeValidCtxt(validCtxt);
      xmlSchemaFreeParserCtxt(schemaCtxt);
      xmlFreeDoc(doc);
    }

    xmlFreeParserCtxt(ctxt);
  }

exit:
  xmlFuzzMemSetLimit(0);
  xmlFuzzDataCleanup();
  xmlResetLastError();
  return (0);
}