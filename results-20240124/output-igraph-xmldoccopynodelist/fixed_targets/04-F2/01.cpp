#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xpath.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  xmlDocPtr doc = xmlParseMemory((const char*)data, size);
  if (doc == nullptr) {
    return 0;
  }
  xmlNodePtr node = xmlDocGetRootElement(doc);
  xmlDocCopyNodeList(doc, node);
  xmlFreeDoc(doc);
  return 0;
}