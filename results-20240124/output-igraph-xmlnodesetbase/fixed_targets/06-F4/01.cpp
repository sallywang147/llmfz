#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <libxml/xmlwriter.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  xmlDocPtr doc = xmlNewDoc(nullptr);
  if (doc == nullptr) {
    return 0;
  }

  xmlNodePtr root = xmlNewNode(nullptr, (const xmlChar*)"root");
  if (root == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  xmlDocSetRootElement(doc, root);

  xmlNodePtr cur = root;
  while (stream.remaining_bytes() > 0) {
    xmlNodePtr child = xmlNewNode(nullptr, (const xmlChar*)"child");
    if (child == nullptr) {
      xmlFreeDoc(doc);
      return 0;
    }

    xmlAddChild(cur, child);
    cur = child;
  }

  std::string uri = stream.ConsumeRemainingBytesAsString();
  xmlNodeSetBase(cur, (char*)uri.c_str());

  xmlFreeDoc(doc);
  return 0;
}