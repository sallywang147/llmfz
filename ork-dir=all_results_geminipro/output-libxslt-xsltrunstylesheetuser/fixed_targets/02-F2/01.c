#include <fuzz.h>

extern "C" {
#include <libxslt/xslt.h>
#include <libxml/parser.h>
}

int LLVMFuzzerInitialize(int *argc_p ATTRIBUTE_UNUSED, char ***argv_p ATTRIBUTE_UNUSED) { return xsltFuzzInit(); }

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  xmlDocPtr xmlDoc = xsltFuzzParseDoc(data, size);
  if (xmlDoc == NULL) {
    return 0;
  }

  xsltStylesheetPtr style = xsltFuzzParseStylesheet(data, size);
  if (style == NULL) {
    xmlFreeDoc(xmlDoc);
    return 0;
  }

  char *output = xsltFuzzRunStylesheetUser(style, xmlDoc, NULL, NULL, NULL, NULL, NULL, NULL);
  xsltFreeStylesheet(style);
  xmlFreeDoc(xmlDoc);
  xsltFuzzFreeString(output);

  return 0;
}

int xsltRunStylesheetUser(xsltStylesheetPtr style, xmlDocPtr doc, char **params, char *output, xmlSAXHandlerPtr sax, xmlOutputBufferPtr iobuf, FILE *profile, xsltTransformContextPtr userCtxt) {
  return xsltApplyStylesheetUser(style, doc, output, params, sax, iobuf, profile, userCtxt);
}