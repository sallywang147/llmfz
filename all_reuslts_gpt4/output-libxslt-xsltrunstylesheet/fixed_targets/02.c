#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxslt/transform.h"
#include "libxslt/xsltutils.h"
#include "libxml/parser.h"
#include "libxml/xmlIO.h"
#include "libxml/xmlversion.h"
#include "libxml/xmlerror.h"
#include "libxml/tree.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize libxml and libxslt libraries.
  xmlInitParser();
  LIBXML_TEST_VERSION
  xmlSetGenericErrorFunc(NULL, NULL);
  xsltInit();

  // Create a new XSLT stylesheet object.
  xsltStylesheetPtr style = xsltNewStylesheet();
  if (style == NULL) {
    return 0;
  }

  // Create a new XML document object.
  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
  if (doc == NULL) {
    xsltFreeStylesheet(style);
    return 0;
  }

  // Create a new XML SAX handler object.
  xmlSAXHandlerPtr SAX = (xmlSAXHandlerPtr) xmlMalloc(sizeof(xmlSAXHandler));
  if (SAX == NULL) {
    xmlFreeDoc(doc);
    xsltFreeStylesheet(style);
    return 0;
  }
  memset(SAX, 0, sizeof(xmlSAXHandler));

  // Create a new XML output buffer object.
  xmlOutputBufferPtr IObuf = xmlAllocOutputBuffer(NULL);
  if (IObuf == NULL) {
    xmlFree(SAX);
    xmlFreeDoc(doc);
    xsltFreeStylesheet(style);
    return 0;
  }

  // Consume the data to create a null-terminated string.
  std::string output = stream.ConsumeRemainingBytesAsString();
  char* params[2] = {NULL, NULL};

  // Call the function to be tested.
  xsltRunStylesheet(style, doc, params, const_cast<char*>(output.c_str()), SAX, IObuf);

  // Cleanup.
  xmlOutputBufferClose(IObuf);
  xmlFree(SAX);
  xmlFreeDoc(doc);
  xsltFreeStylesheet(style);
  xmlCleanupParser();
  xsltCleanupGlobals();

  return 0;
}