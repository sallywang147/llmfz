#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxslt/transform.h"
#include "libxslt/xsltutils.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  // Initialize libxml2 and libxslt libraries.
  xmlInitParser();
  LIBXML_TEST_VERSION
  xmlSubstituteEntitiesDefault(1);
  xmlLoadExtDtdDefaultValue = 1;
  exsltRegisterAll();

  FuzzedDataProvider stream(data, size);

  // Create a xsltStylesheetPtr from the input data.
  xmlDocPtr styleDoc = xmlReadMemory(reinterpret_cast<const char*>(data), size, "noname.xml", NULL, 0);
  xsltStylesheetPtr style = xsltParseStylesheetDoc(styleDoc);
  if (style == NULL) {
    xmlFreeDoc(styleDoc);
    return 0;
  }

  // Create a xmlDocPtr for the transformation.
  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
  xmlNodePtr root = xmlNewNode(NULL, BAD_CAST "root");
  xmlDocSetRootElement(doc, root);

  // No parameters for the transformation.
  const char **params = NULL;

  // Output will be written to this buffer.
  xmlOutputBufferPtr outputBuffer = xmlAllocOutputBuffer(NULL);
  if (outputBuffer == NULL) {
    xsltFreeStylesheet(style);
    xmlFreeDoc(doc);
    return 0;
  }

  // No SAX handler for the transformation.
  xmlSAXHandlerPtr SAX = NULL;

  // No profiling for the transformation.
  FILE *profile = NULL;

  // No user context for the transformation.
  xsltTransformContextPtr userCtxt = NULL;

  // Run the transformation.
  int ret = xsltRunStylesheetUser(style, doc, params, NULL, SAX, outputBuffer, profile, userCtxt);

  // Cleanup.
  xmlOutputBufferClose(outputBuffer);
  xsltFreeStylesheet(style);
  xmlFreeDoc(doc);
  xsltCleanupGlobals();
  xmlCleanupParser();

  return 0;
}