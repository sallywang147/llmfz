#include "fuzz.h"

extern "C" {
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xslt.h>
}

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xsltFuzzInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlDocPtr doc = xsltFuzzParseDoc(data, size);
  if (doc == NULL) {
    return 0;
  }

  xsltStylesheetPtr style = xsltFuzzParseStylesheet(data, size);
  if (style == NULL) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlOutputBufferPtr output = xmlOutputBufferCreateBuffer(NULL, NULL);
  if (output == NULL) {
    xmlFreeDoc(doc);
    xsltFreeStylesheet(style);
    return 0;
  }

  xsltProcessStylesheet(style, doc);
  xsltSaveResultToOutput(output, style, doc);

  xmlOutputBufferClose(output);
  xmlFreeDoc(doc);
  xsltFreeStylesheet(style);

  return 0;
}