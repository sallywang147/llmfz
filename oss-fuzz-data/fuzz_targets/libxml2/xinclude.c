/*
 * xinclude.c: a libFuzzer target to test the XInclude engine.
 *
 * See Copyright for the status of this software.
 */

#include "fuzz.h"
#include <libxml/catalog.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xinclude.h>
#include <libxml/xmlerror.h>
#include <libxml/xmlreader.h>

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
  const char *docBuffer, *docUrl;
  size_t maxAlloc, docSize;
  int opts;

  xmlFuzzDataInit(data, size);
  opts = (int)xmlFuzzReadInt(4);
  opts |= XML_PARSE_XINCLUDE;
  maxAlloc = xmlFuzzReadInt(4) % (size + 100);

  xmlFuzzReadEntities();
  docBuffer = xmlFuzzMainEntity(&docSize);
  docUrl = xmlFuzzMainUrl();
  if (docBuffer == NULL)
    goto exit;

  /* Pull parser */

  xmlFuzzMemSetLimit(maxAlloc);
  ctxt = xmlNewParserCtxt();
  if (ctxt != NULL) {
    xmlXIncludeCtxtPtr xinc;
    xmlDocPtr copy;

    doc = xmlCtxtReadMemory(ctxt, docBuffer, docSize, docUrl, NULL, opts);
    xmlFuzzCheckMallocFailure("xmlCtxtReadMemory", ctxt->errNo == XML_ERR_NO_MEMORY);

    xmlFuzzResetMallocFailed();
    xinc = xmlXIncludeNewContext(doc);
    xmlXIncludeSetFlags(xinc, opts);
    xmlXIncludeProcessNode(xinc, (xmlNodePtr)doc);
    if (doc != NULL) {
      xmlFuzzCheckMallocFailure("xmlXIncludeProcessNode", xinc == NULL || xmlXIncludeGetLastError(xinc) == XML_ERR_NO_MEMORY);
    }
    xmlXIncludeFreeContext(xinc);

    xmlFuzzResetMallocFailed();
    copy = xmlCopyDoc(doc, 1);
    if (doc != NULL)
      xmlFuzzCheckMallocFailure("xmlCopyNode", copy == NULL);
    xmlFreeDoc(copy);

    xmlFreeDoc(doc);
    xmlFreeParserCtxt(ctxt);
  }

  /* Reader */

#ifdef LIBXML_READER_ENABLED
  {
    xmlTextReaderPtr reader;
    int j;

    xmlFuzzMemSetLimit(maxAlloc);
    reader = xmlReaderForMemory(docBuffer, docSize, NULL, NULL, opts);
    if (reader == NULL)
      goto exit;
    while (xmlTextReaderRead(reader) == 1) {
      if (xmlTextReaderNodeType(reader) == XML_ELEMENT_NODE) {
        int i, n = xmlTextReaderAttributeCount(reader);
        for (i = 0; i < n; i++) {
          xmlTextReaderMoveToAttributeNo(reader, i);
          while (xmlTextReaderReadAttributeValue(reader) == 1)
            ;
        }
      }
    }
    for (j = 0; j < 10; j++)
      xmlTextReaderRead(reader);
    xmlFreeTextReader(reader);
  }
#endif

exit:
  xmlFuzzMemSetLimit(0);
  xmlFuzzDataCleanup();
  xmlResetLastError();
  return (0);
}
