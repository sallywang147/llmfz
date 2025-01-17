#include <fuzzer/FuzzedDataProvider.h>
#include "expat.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  // Consume 1/3 of the data for arg1
  std::string arg1 = stream.ConsumeBytesAsString(size / 3);
  // Consume 1/3 of the data for arg2
  std::string arg2 = stream.ConsumeBytesAsString(size / 3);
  // Consume the rest of the data for arg3
  std::string arg3 = stream.ConsumeRemainingBytesAsString();

  char *argv[] = { (char *)arg3.c_str(), NULL };

  externalEntityInitProcessor(parser, (char *)arg1.c_str(), (char *)arg2.c_str(), argv);

  XML_ParserFree(parser);

  return 0;
}