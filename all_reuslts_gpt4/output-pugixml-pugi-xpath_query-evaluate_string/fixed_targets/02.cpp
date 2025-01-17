#include <fuzzer/FuzzedDataProvider.h>
#include <pugixml.hpp>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_string(reinterpret_cast<const char*>(data), pugi::parse_default);
  if (!result) {
    return 0;
  }

  std::string xpathExpr = stream.ConsumeRandomLengthString();
  pugi::xpath_query query(xpathExpr.c_str());
  if (!query) {
    return 0;
  }

  pugi::xpath_node node = doc.select_node(xpathExpr.c_str());
  if (!node) {
    return 0;
  }

  std::vector<char> buffer(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  query.evaluate_string(buffer.data(), buffer.size(), &node);

  return 0;
}