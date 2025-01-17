#include <fuzzer/FuzzedDataProvider.h>
#include "tinyxml2/tinyxml2.h"

using namespace tinyxml2;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Split the data into two parts
  const size_t first_size = stream.ConsumeIntegralInRange<size_t>(1, size - 1);
  const std::string first_part = stream.ConsumeBytesAsString(first_size);
  const std::string second_part = stream.ConsumeRemainingBytesAsString();

  // Parse the first part into a document
  XMLDocument doc1;
  if (doc1.Parse(first_part.c_str()) != XML_SUCCESS) {
    return 0;
  }

  // Parse the second part into a document
  XMLDocument doc2;
  if (doc2.Parse(second_part.c_str()) != XML_SUCCESS) {
    return 0;
  }

  // Get the root elements of both documents
  XMLElement *root1 = doc1.RootElement();
  XMLElement *root2 = doc2.RootElement();

  // If either document has no root, return
  if (!root1 || !root2) {
    return 0;
  }

  // Compare the roots
  root1->ShallowEqual(root2);

  return 0;
}