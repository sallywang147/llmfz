#include <fuzzer/FuzzedDataProvider.h>
#include <ixml.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string buffer = stream.ConsumeRemainingBytesAsString();
  IXML_Document *doc = nullptr;

  ixmlParseBufferEx(const_cast<char *>(buffer.c_str()), &doc);

  if (doc) {
    ixmlDocument_free(doc);
  }

  return 0;
}