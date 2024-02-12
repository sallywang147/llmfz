#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <libxml/parser.h>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlReadMemory(reinterpret_cast<const char*>(data), size,
                                "noname.xml", nullptr, 0);
  if (doc == nullptr) {
    return 0;
  }
  xmlNodePtr cur = xmlDocGetRootElement(doc);
  if (cur == nullptr) {
    xmlFreeDoc(doc);
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  const std::string base = stream.ConsumeRemainingBytesAsString();
  xmlNodeSetBase(cur, const_cast<char*>(base.c_str()));

  xmlFreeDoc(doc);
  return 0;
}