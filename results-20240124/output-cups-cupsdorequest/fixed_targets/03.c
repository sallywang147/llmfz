#include "cups.h"
#include "ipp.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <algorithm>
#include <cups/http.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string resource = stream.ConsumeRemainingBytesAsString();
  http_t *http = httpNew();
  ipp_t *request = ippNew();
  cupsDoRequest(http, request, resource.c_str());
  httpDelete(http, NULL);
  ippDelete(request);
  return 0;
}