#include "fuzzer/FuzzedDataProvider.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libxslt/xsltInternals.h"
#include "libxslt/xslt.h"
#include "libxml2/libxml/parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Split the data into two parts: one for the stylesheet, one for the XML document.
  size_t stylesheet_size = stream.ConsumeIntegralInRange<size_t>(0, size - 2);
  std::string stylesheet_string = stream.ConsumeBytesAsString(stylesheet_size);
  std::string xml_string = stream.ConsumeRemainingBytesAsString();

  // Parse the stylesheet and the XML document.
  xmlDocPtr stylesheet_doc = xmlReadMemory(stylesheet_string.data(), stylesheet_string.size(), "noname.xml", NULL, 0);
  if (stylesheet_doc == NULL) {
    return 0;
  }
  xsltStylesheetPtr style = xsltParseStylesheetDoc(stylesheet_doc);
  if (style == NULL) {
    xmlFreeDoc(stylesheet_doc);
    return 0;
  }

  xmlDocPtr doc = xmlReadMemory(xml_string.data(), xml_string.size(), "noname.xml", NULL, 0);
  if (doc == NULL) {
    xsltFreeStylesheet(style);
    return 0;
  }

  // Call the target function.
  xmlDocPtr result_doc = xsltProfileStylesheet(style, doc, NULL, NULL);

  // Clean up.
  if (result_doc != NULL) {
    xmlFreeDoc(result_doc);
  }
  xmlFreeDoc(doc);
  xsltFreeStylesheet(style);

  return 0;
}