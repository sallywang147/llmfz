#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create XML document and root node
  XMLDocument doc;
  XMLElement* root = doc.NewElement("root");
  doc.InsertFirstChild(root);

  // Create two child nodes
  XMLElement* child1 = doc.NewElement("child1");
  XMLElement* child2 = doc.NewElement("child2");

  // Insert the first child node
  root->InsertFirstChild(child1);

  // Insert the second child node after the first
  root->InsertAfterChild(child1, child2);

  return 0;
}