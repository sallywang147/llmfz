 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <libxml/parser.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  xmlDocPtr doc = xmlParseMemory((const char *)Data, Size);
  if (doc == nullptr) {
    return 0;
  }

  xmlNodePtr node = xmlDocGetRootElement(doc);
  if (node == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlCopyNodeList(node);

  xmlFreeDoc(doc);
  return 0;
}