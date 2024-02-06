#include <fuzzer/FuzzedDataProvider.h>
#include <pugixml.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create XML document and node
  pugi::xml_document doc;
  pugi::xml_node node = doc.append_child("node");

  // Consume data to create query string
  std::string query = stream.ConsumeRandomLengthString();
  char *query_cstr = const_cast<char*>(query.c_str());

  // Create and populate xpath_variable_set
  pugi::xpath_variable_set variables;
  if (stream.remaining_bytes() > 0) {
    std::string variable_name = stream.ConsumeRandomLengthString();
    std::string variable_value = stream.ConsumeRandomLengthString();
    variables.set(variable_name.c_str(), variable_value.c_str());
  }

  // Call function under test
  node.select_single_node(query_cstr, &variables);

  return 0;
}