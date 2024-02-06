#include <fuzzer/FuzzedDataProvider.h>
#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Consume 1 byte for namespace separator
  char ns_sep = stream.ConsumeIntegral<char>();

  // Consume the rest of the data as encoding name
  std::string encoding = stream.ConsumeRemainingBytesAsString();
  
  // Create the parser
  XML_Parser parser = XML_ParserCreateNS(encoding.c_str(), ns_sep);
  if (parser) {
    XML_ParserFree(parser);
  }

  return 0;
}