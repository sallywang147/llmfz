#include <fuzzer/FuzzedDataProvider.h>

#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlNewDoc(nullptr);
  if (doc == nullptr) {
    return 0;
  }

  xmlNodePtr root_node = xmlNewNode(nullptr, (const xmlChar*)"root");
  if (root_node == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlDocSetRootElement(doc, root_node);

  FuzzedDataProvider stream(data, size);
  for (int i = 0; i < 100; i++) {
    const std::string tag_name = stream.ConsumeRandomLengthString();
    xmlNodePtr child_node = xmlNewNode(nullptr, (const xmlChar*)tag_name.c_str());
    if (child_node == nullptr) {
      xmlFreeDoc(doc);
      return 0;
    }
    xmlAddChild(root_node, child_node);
  }

  xmlNodePtr copy = xmlDocCopyNodeList(doc, root_node);
  xmlFreeDoc(doc);
  xmlFreeNode(copy);
  return 0;
}