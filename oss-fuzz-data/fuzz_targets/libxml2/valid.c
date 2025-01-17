/*
 * valid.c: a libFuzzer target to test DTD validation.
 *
 * See Copyright for the status of this software.
 */

#include "fuzz.h"
#include <libxml/catalog.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
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
  xmlValidCtxtPtr vctxt;
  const char *docBuffer, *docUrl;
  size_t maxAlloc, docSize;
  int opts;

  xmlFuzzDataInit(data, size);
  opts = (int)xmlFuzzReadInt(4);
  opts &= ~XML_PARSE_XINCLUDE;
  opts |= XML_PARSE_DTDVALID;
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
    doc = xmlCtxtReadMemory(ctxt, docBuffer, docSize, docUrl, NULL, opts);
    xmlFuzzCheckMallocFailure("xmlCtxtReadMemory", ctxt->errNo == XML_ERR_NO_MEMORY);
    xmlFreeDoc(doc);
    xmlFreeParserCtxt(ctxt);
  }

  /* Post validation */

  xmlFuzzMemSetLimit(maxAlloc);
  doc = xmlReadMemory(docBuffer, docSize, docUrl, NULL, opts & ~XML_PARSE_DTDVALID);
  vctxt = xmlNewValidCtxt();
  xmlValidateDocument(vctxt, doc);
  xmlFreeValidCtxt(vctxt);
  xmlFreeDoc(doc);

  /* Push parser */

#ifdef LIBXML_PUSH_ENABLED
  {
    static const size_t maxChunkSize = 128;
    size_t consumed, chunkSize;

    xmlFuzzMemSetLimit(maxAlloc);
    ctxt = xmlCreatePushParserCtxt(NULL, NULL, NULL, 0, docUrl);
    if (ctxt != NULL) {
      xmlCtxtUseOptions(ctxt, opts);

      for (consumed = 0; consumed < docSize; consumed += chunkSize) {
        chunkSize = docSize - consumed;
        if (chunkSize > maxChunkSize)
          chunkSize = maxChunkSize;
        xmlParseChunk(ctxt, docBuffer + consumed, chunkSize, 0);
      }

      xmlParseChunk(ctxt, NULL, 0, 1);
      xmlFuzzCheckMallocFailure("xmlParseChunk", ctxt->errNo == XML_ERR_NO_MEMORY);
      xmlFreeDoc(ctxt->myDoc);
      xmlFreeParserCtxt(ctxt);
    }
  }
#endif

  /* Reader */

#ifdef LIBXML_READER_ENABLED
  {
    xmlTextReaderPtr reader;
    const xmlError *error;
    int j;

    xmlFuzzMemSetLimit(maxAlloc);
    reader = xmlReaderForMemory(docBuffer, docSize, NULL, NULL, opts);
    if (reader != NULL) {
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
      error = xmlTextReaderGetLastError(reader);
      xmlFuzzCheckMallocFailure("xmlTextReaderRead", error->code == XML_ERR_NO_MEMORY);
      xmlFreeTextReader(reader);
    }
  }
#endif

exit:
  xmlFuzzMemSetLimit(0);
  xmlFuzzDataCleanup();
  xmlResetLastError();
  return (0);
}
