#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xpath.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlReadMemory(reinterpret_cast<const char*>(data), size,
                                "noname.xml", NULL, 0);
  if (doc == nullptr) {
    return 0;
  }

  xmlNodePtr root = xmlDocGetRootElement(doc);
  if (root == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlNodePtr node = root;
  while (node != nullptr) {
    xmlNodePtr next = node->next;
    xmlCopyNodeList(node);
    node = next;
  }

  xmlFreeDoc(doc);
  return 0;
}