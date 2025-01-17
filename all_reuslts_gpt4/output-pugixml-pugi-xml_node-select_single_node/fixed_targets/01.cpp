#include <fuzzer/FuzzedDataProvider.h>
#include <pugixml.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create an xml document
    pugi::xml_document doc;
    if (!doc.load_string("<root><node/></root>")) {
        return 0;
    }

    // Create an xml_node instance
    pugi::xml_node node = doc.child("root");

    // Extract a string to use as a query
    std::string query = stream.ConsumeRandomLengthString();
    if (query.empty()) {
        return 0;
    }

    // Create an xpath_variable_set instance
    pugi::xpath_variable_set variables;

    // Call the function to fuzz
    try {
        node.select_single_node(query.c_str(), &variables);
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}