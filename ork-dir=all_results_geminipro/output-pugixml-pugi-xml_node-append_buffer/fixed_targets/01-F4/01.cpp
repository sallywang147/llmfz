#include "../src/pugixml.hpp"
#include "fuzzer/FuzzedDataProvider.h"

#include <stdint.h>
#include <string.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fdp(Data, Size);
  std::string text = fdp.ConsumeRandomLengthString(1024);

#ifndef PUGIXML_NO_EXCEPTIONS
  try
#endif
  {
    pugi::xml_document doc;
    doc.load_string(text.c_str());

    std::vector<uint8_t> xml_buffer = fdp.ConsumeBytes<uint8_t>(fdp.ConsumeIntegralInRange(0, 1024));
    pugi::xml_parse_result result = doc.load_buffer_inplace(xml_buffer.data(), xml_buffer.size(), pugi::parse_full, pugi::encoding_utf8);
    if (result) {
      pugi::xml_node node = doc.child("node");
      if (!node.empty()) {
        pugi::xml_node contents = node.first_child();
        pugi::xml_node::append_buffer(result, &contents, nullptr, 0, pugi::encoding_utf8, 0);  // Fix: Use 'result' as the first argument
      }
    }
  }
#ifndef PUGIXML_NO_EXCEPTIONS
  catch (pugi::xpath_exception &) {
  }
#endif
  return 0;
}