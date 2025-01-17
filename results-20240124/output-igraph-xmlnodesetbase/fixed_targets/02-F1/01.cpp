#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string uri = stream.ConsumeRemainingBytesAsString();
  xmlNodePtr cur = xmlNewNode(nullptr, reinterpret_cast<const xmlChar*>(uri.c_str()));
  xmlNodeSetBase(cur, reinterpret_cast<char*>(const_cast<char*>(uri.c_str())));
  xmlFreeNode(cur);
  return 0;
}