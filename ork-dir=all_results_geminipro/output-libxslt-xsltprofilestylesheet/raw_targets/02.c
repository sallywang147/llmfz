#include "fuzz.h"

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xsltFuzzXPathInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlXPathObjectPtr xpathObj = xsltFuzzXPath(data, size);
  xmlDocPtr doc = xsltFuzzDoc(data, size);
  xmlDocPtr ret = xsltProfileStylesheet(xsltFuzzStylesheet(data, size), doc, nullptr, nullptr);
  xsltFuzzFreeDoc(doc);
  xsltFuzzFreeDoc(ret);
  xsltFuzzXPathFreeObject(xpathObj);

  return 0;
}