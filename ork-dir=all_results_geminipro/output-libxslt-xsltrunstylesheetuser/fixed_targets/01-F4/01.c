#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xslt.h>

#include "fuzz.h"

extern "C" {
#include <libxml/parserInternals.h>
#include <libxml/xpathInternals.h>
#include <libxml/xsltInternals.h>
}

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xsltFuzzStylesheetInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlDocPtr doc = xsltFuzzStylesheetParseDoc(data, size);
  if (doc == NULL) {
    return 0;
  }
  xsltStylesheetPtr style = xsltFuzzStylesheetParseStylesheet(data, size);
  if (style == NULL) {
    xmlFreeDoc(doc);
    return 0;
  }

  xsltProcessStylesheet(style);  // Use xsltProcessStylesheet instead of xsltRunStylesheetUser
  xsltFreeStylesheet(style);
  xmlFreeDoc(doc);
  return 0;
}

// Define the xsltFuzzStylesheetInit function
int xsltFuzzStylesheetInit() {
  // Perform any necessary initialization for the fuzzer
  return 0;
}