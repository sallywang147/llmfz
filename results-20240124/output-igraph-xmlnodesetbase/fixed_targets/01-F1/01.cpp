#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlwriter.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
  xmlNodePtr root = xmlNewNode(nullptr, BAD_CAST "root");
  xmlDocSetRootElement(doc, root);
  std::string uri = stream.ConsumeRemainingBytesAsString();
  xmlNodeSetBase(root, const_cast<char*>(uri.c_str()));
  xmlFreeDoc(doc);
  return 0;
}