#include "fuzz.h"

extern "C" {
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xinclude.h>
#include <libxml/tree.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
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
  xsltRunStylesheet(style, doc, NULL, NULL, NULL, NULL);
  xsltFreeStylesheet(style);
  xmlFreeDoc(doc);
  return 0;
}