 #include "cups.h"
#include "ipp.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *resource = stream.ConsumeRemainingBytesAsString().c_str();
  cups_http_t *http = cupsHttpNew();
  ipp_t *request = ippNew();
  cupsDoRequest(http, request, resource);
  cupsHttpDelete(http);
  ippDelete(request);
  return 0;
}