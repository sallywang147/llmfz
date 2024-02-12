 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
  FuzzedDataProvider stream(data, size);
  char *encoding = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 16)).c_str();
  char sep = stream.ConsumeIntegral<char>();

  XML_Parser parser = XML_ParserCreateNS(encoding, sep);
  if (parser)
    XML_ParserFree(parser);

  return 0;
}