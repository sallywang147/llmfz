#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "libxml/parser.h"
#include "libxml/tree.h"

extern "C" {
#include "libxml/xpath.h"
#include "libxml/xmlschemastypes.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();

  xmlDocPtr doc = xmlParseFile(filename.c_str());
  if (doc == nullptr) {
    return 0;
  }

  xmlShellCmd(doc, const_cast<char*>(filename.c_str()), nullptr, nullptr);

  xmlFreeDoc(doc);
  xmlCleanupParser();
  return 0;
}