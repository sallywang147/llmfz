#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ixml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ixml library
  ixmlRelaxParser(1);

  // Create a node
  IXML_Node* node = (IXML_Node*)ixmlElement_create("FuzzNode");
  if(node == nullptr) {
    return 0;
  }

  // Set node value
  const std::string nodeValue = stream.ConsumeRandomLengthString();
  ixmlNode_setNodeValue(node, nodeValue.c_str());

  // Set deep value
  int deep = stream.ConsumeIntegral<int>();

  // Call the target function
  IXML_Node* clonedNode = ixmlNode_cloneNodeTreeRecursive(node, deep);

  // Clean up
  ixmlNode_free(node);
  ixmlNode_free(clonedNode);

  return 0;
}