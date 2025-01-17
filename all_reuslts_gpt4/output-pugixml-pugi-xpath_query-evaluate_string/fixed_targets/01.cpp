#include <fuzzer/FuzzedDataProvider.h>
#include <pugixml.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an XML document
  pugi::xml_document doc;
  if (!doc.load("<root><child>text</child></root>")) {
    return 0;
  }

  // Extract a string to use as XPath query
  std::string query = stream.ConsumeRandomLengthString();
  pugi::xpath_query xpath_query(query.c_str());

  // Create an XPath node
  pugi::xpath_node node(doc.child("root"));

  // Extract a size for the buffer
  size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);

  // Create a buffer
  std::vector<char> buffer(buffer_size);

  // Call the function to fuzz
  xpath_query.evaluate_string(buffer.data(), buffer.size(), &node);

  return 0;
}