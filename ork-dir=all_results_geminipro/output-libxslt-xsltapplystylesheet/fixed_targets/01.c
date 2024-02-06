#include "fuzz.h"

extern "C" {
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xslt.h>
}

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xsltFuzzXPathInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlDocPtr doc = xsltFuzzXPathParseDoc(data, size);
  if (doc == NULL) {
    return 0;
  }

  xsltStylesheetPtr style = xsltFuzzXPathParseStylesheet(data, size);
  if (style == NULL) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlDocPtr result = xsltApplyStylesheet(style, doc, NULL);
  if (result != NULL) {
    xmlSaveFormatFileEnc("-", result, "UTF-8", 1);
    xmlFreeDoc(result);
  }

  xsltFreeStylesheet(style);
  xmlFreeDoc(doc);

  return 0;
}