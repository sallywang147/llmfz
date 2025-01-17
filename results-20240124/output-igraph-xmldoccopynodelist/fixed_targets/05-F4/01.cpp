#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlwriter.h>
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

  xmlDocCopyNodeList(doc, node);

  xmlFreeDoc(doc);
  return 0;
}