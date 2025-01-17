#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ixml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize the document and node
  IXML_Document* doc = ixmlDocument_createDocument();
  IXML_Node* importNode = (IXML_Node*)ixmlDocument_createElement(doc, "test");
  IXML_Node* rtNode = NULL;

  // Consume data from the provider
  int deep = provider.ConsumeIntegral<int>();

  // Call the function under test
  int result = ixmlDocument_importNode(doc, importNode, deep, &rtNode);

  // Clean up
  ixmlNode_free((IXML_Node*)doc);
  ixmlNode_free(importNode);

  return 0;
}