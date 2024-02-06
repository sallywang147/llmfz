#include <fuzzer/FuzzedDataProvider.h>
#include <ixml.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string buffer = stream.ConsumeRemainingBytesAsString();
  IXML_Document* doc = NULL;

  int ret = ixmlParseBufferEx(const_cast<char*>(buffer.c_str()), &doc);
  if (ret == IXML_SUCCESS && doc != NULL) {
    ixmlDocument_free(doc);
  }

  return 0;
}