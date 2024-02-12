 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <libxml/parser.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  xmlDocPtr doc = xmlReadMemory((const char*)data, size, NULL, NULL, 0);
  if (doc == NULL) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  const std::string uri = stream.ConsumeRemainingBytesAsString();

  xmlNodeSetBase(xmlDocGetRootElement(doc), const_cast<char*>(uri.c_str()));

  xmlFreeDoc(doc);
  return 0;
}