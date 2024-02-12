#include <algorithm>
#include "cups/cups.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string resource = stream.ConsumeRemainingBytesAsString();
  cups_http_t *http = cupsConnect(NULL, 631, 0);
  if (!http) {
    return 0;
  }
  ipp_t *request = ippNewRequest(IPP_GET_PRINTER_ATTRIBUTES);
  if (!request) {
    cupsDisconnect(http);
    return 0;
  }
  cupsDoRequest(http, request, resource.c_str());
  ippDelete(request);
  cupsDisconnect(http);
  return 0;
}

}