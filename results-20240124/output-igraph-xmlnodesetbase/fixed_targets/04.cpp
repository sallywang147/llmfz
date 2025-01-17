#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlParseMemory((const char*)data, size);
  if (doc == nullptr) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  xmlNodePtr cur = xmlDocGetRootElement(doc);
  if (cur == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  std::string uri = stream.ConsumeRemainingBytesAsString();
  xmlNodeSetBase(cur, (char*)uri.c_str());

  xmlFreeDoc(doc);
  return 0;
}