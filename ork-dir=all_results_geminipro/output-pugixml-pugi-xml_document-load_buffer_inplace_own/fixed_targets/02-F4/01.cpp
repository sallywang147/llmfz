#include "../src/pugixml.hpp"
#include "fuzzer/FuzzedDataProvider.h"

#include <stdint.h>
#include <string.h>
#include <string>

extern "C" {
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fdp(Data, Size);
  std::string text = fdp.ConsumeRandomLengthString(1024);

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_buffer_inplace(text.c_str(), text.size());

  (void)result;

  return 0;
}
```
The issue was in the `load_buffer_inplace_own` function. The correct function to use is `load_buffer_inplace`.