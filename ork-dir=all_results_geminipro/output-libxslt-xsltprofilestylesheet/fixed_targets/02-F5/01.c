#include "fuzz.h"

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

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

DEFINE_FUZZER(LLVMFuzzerTestOneInput)

// Definitions of the missing functions.
int xsltFuzzXPathInit() { return 0; }

xmlXPathObjectPtr xsltFuzzXPath(const char *data, size_t size) { return nullptr; }

xmlDocPtr xsltFuzzDoc(const char *data, size_t size) { return nullptr; }

xmlDocPtr xsltFuzzStylesheet(const char *data, size_t size) { return nullptr; }

xmlDocPtr xsltProfileStylesheet(xmlDocPtr stylesheet, xmlDocPtr doc, const char *params, const char *output) { return nullptr; }

void xsltFuzzFreeDoc(xmlDocPtr doc) {}

void xsltFuzzXPathFreeObject(xmlXPathObjectPtr xpathObj) {}