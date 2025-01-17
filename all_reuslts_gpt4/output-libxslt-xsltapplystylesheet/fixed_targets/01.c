#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxslt/transform.h"
#include "libxslt/xsltutils.h"
#include "libxml/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Prepare the stylesheet
  xmlDocPtr styleDoc = xmlReadMemory(reinterpret_cast<const char*>(stream.ConsumeBytesAsString(1).c_str()), 1, "noname.xml", NULL, 0);
  xsltStylesheetPtr style = xsltParseStylesheetDoc(styleDoc);
  if (!style) {
    xmlFreeDoc(styleDoc);
    return 0;
  }

  // Prepare the document
  xmlDocPtr doc = xmlReadMemory(reinterpret_cast<const char*>(stream.ConsumeBytesAsString(1).c_str()), 1, "noname.xml", NULL, 0);
  if (!doc) {
    xsltFreeStylesheet(style);
    return 0;
  }

  // Prepare the parameters
  char* params[2] = { nullptr, nullptr };
  params[0] = const_cast<char*>(stream.ConsumeRemainingBytesAsString().c_str());

  // Apply the stylesheet
  xmlDocPtr res = xsltApplyStylesheet(style, doc, params);

  // Cleanup
  xsltFreeStylesheet(style);
  xmlFreeDoc(doc);
  xmlFreeDoc(res);

  return 0;
}