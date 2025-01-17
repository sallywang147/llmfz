#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlParseMemory((const char*)data, size);
  if (doc == nullptr) {
    return 0;
  }
  xmlNodePtr node = xmlDocGetRootElement(doc);
  if (node == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }
  struct _xmlNode *copy = xmlCopyNodeList(node);
  xmlFreeDoc(doc);
  xmlFreeNodeList(copy);
  return 0;
}