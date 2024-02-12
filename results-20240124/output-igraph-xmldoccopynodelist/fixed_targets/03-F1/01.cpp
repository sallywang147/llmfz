#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <libxml/parser.h>
#include <libxml/xpath.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlReadMemory((const char*)data, size, NULL, NULL, 0);
  if (doc == nullptr) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  xmlNodePtr node = xmlDocGetRootElement(doc);
  while (node != nullptr) {
    const int depth = stream.ConsumeIntegralInRange<int>(0, 10);
    for (int i = 0; i < depth; ++i) {
      node = node->children;
    }
  }

  xmlDocCopyNodeList(doc, node);

  xmlFreeDoc(doc);
  return 0;
}