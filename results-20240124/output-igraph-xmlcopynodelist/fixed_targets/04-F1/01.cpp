#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  xmlDocPtr doc = xmlReadMemory(reinterpret_cast<const char*>(data), size,
                                "noname.xml", nullptr, 0);
  if (doc == nullptr) {
    return 0;
  }

  xmlNodePtr node = xmlDocGetRootElement(doc);
  while (node != nullptr && node->type != XML_ELEMENT_NODE) {
    node = node->next;
  }
  if (node == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlNodePtr copy = xmlCopyNodeList(node);
  if (copy != nullptr) {
    xmlFreeNodeList(copy);
  }

  xmlFreeDoc(doc);
  return 0;
}