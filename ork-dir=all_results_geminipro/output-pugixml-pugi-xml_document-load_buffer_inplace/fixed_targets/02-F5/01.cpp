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
    pugi::xml_parse_result result;
    doc.load_buffer_inplace(&result, text.c_str(), text.size(),
                            fdp.ConsumeIntegralInRange<size_t>(0, 1024),
                            fdp.ConsumeIntegralInRange<int>(0, 1024),
                            fdp.ConsumeIntegralInRange<int>(0, 1024),
                            pugi::parse_default | pugi::parse_fragment);
  }
#ifndef PUGIXML_NO_EXCEPTIONS
  catch (pugi::xpath_exception &) {
  }
#endif
  return 0;
}