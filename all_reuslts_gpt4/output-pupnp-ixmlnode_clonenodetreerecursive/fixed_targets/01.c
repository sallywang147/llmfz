#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ixml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new node
  IXML_Node* node = ixmlNode_createDocumentElement("root");

  // Consume data to decide the depth of the cloning operation
  int deep = stream.ConsumeIntegral<int>();

  // Clone the node
  IXML_Node* clonedNode = ixmlNode_cloneNodeTreeRecursive(node, deep);

  // Free the memory
  ixmlNode_free(node);
  ixmlNode_free(clonedNode);

  return 0;
}