#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  XML_Parser parser = XML_ParserCreate(NULL);
  if (!parser) {
    return 0;
  }

  std::string base = stream.ConsumeRemainingBytesAsString();
  XML_SetBase(parser, base.empty() ? NULL : const_cast<char*>(base.c_str()));

  XML_ParserFree(parser);

  return 0;
}