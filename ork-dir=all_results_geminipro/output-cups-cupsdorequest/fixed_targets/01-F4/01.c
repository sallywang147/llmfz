#include <cups/cups.h>
#include <cups/ipp.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <cups/cups.h>
#include <cups/ipp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string resource = stream.ConsumeRemainingBytesAsString();

  ipp_t* request = ippNewRequest(IPP_GET_PRINTER_ATTRIBUTES);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_CHARSET, "utf-8",
               "get-printer-attributes");
  ippAddString(request, IPP_TAG_PRINTER, IPP_TAG_NAME, "utf-8", "my-printer");

  cups_http_t *http = cupsConnectHttp(nullptr, 631);
  if (!http) {
    ippDelete(request);
    return 0;
  }

  ipp_t* response = cupsDoRequest(http, request, resource.c_str());
  if (response) {
    ippDelete(response);
  }

  cupsDisconnectHttp(http);

  ippDelete(request);

  return 0;
}