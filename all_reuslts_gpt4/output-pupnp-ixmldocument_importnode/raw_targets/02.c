#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ixml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the iXML library
  ixmlRelaxParser(1);

  // Create a new document
  IXML_Document* doc = ixmlDocument_createDocument();
  if (!doc) {
    return 0;
  }

  // Create a new node
  IXML_Node* importNode = ixmlNode_createNode(stream.ConsumeRandomLengthString().c_str(), eELEMENT_NODE);
  if (!importNode) {
    ixmlDocument_free(doc);
    return 0;
  }

  // Consume a boolean value for the 'deep' parameter
  int deep = stream.ConsumeBool();

  // Declare a pointer for the returned node
  IXML_Node* rtNode = nullptr;

  // Call the function to be fuzzed
  ixmlDocument_importNode(doc, importNode, deep, &rtNode);

  // Clean up
  if (rtNode) {
    ixmlNode_free(rtNode);
  }
  ixmlNode_free(importNode);
  ixmlDocument_free(doc);

  return 0;
}