#include "fuzz.h"

extern "C" {
#include <libxml/parser.h>
#include <libxslt/xslt.h>
}

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xsltFuzzInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlDocPtr doc = xsltFuzzParseDoc(data, size);
  if (!doc) {
    return 0;
  }
  xsltStylesheetPtr style = xsltFuzzParseStylesheet(data, size);
  if (!style) {
    xmlFreeDoc(doc);
    return 0;
  }
  xmlDocPtr res = xsltApplyStylesheet(style, doc, NULL);
  xsltFreeStylesheet(style);
  xmlFreeDoc(doc);
  xmlFreeDoc(res);
  return 0;
}