#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  std::string arg1 = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string arg2 = stream.ConsumeRemainingBytesAsString();
  char *argv[] = {arg1.data(), arg2.data(), NULL};

  externalEntityInitProcessor(parser, argv[0], argv[1], argv);
  
  XML_ParserFree(parser);
  return 0;
}