#include <fuzzer/FuzzedDataProvider.h>

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xmlschemas.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlReadMemory(reinterpret_cast<const char*>(data), size, "noname.xml", nullptr, 0);
  if (doc == nullptr) {
    return 0;
  }

  xmlNodeSetPtr nodes = xmlXPathEvalExpression(BAD_CAST "//node()", doc, nullptr);
  if (nodes == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlNodePtr node = nodes->nodeTab[0];
  xmlDocCopyNodeList(doc, node);

  xmlFreeDoc(doc);
  xmlXPathFreeNodeSet(nodes);

  return 0;
}