 #include <cups/cups.h>
#include <cups/http.h>
#include <cups/ipp.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  cups_http_t *http = cupsHttpNew();
  cupsHttpSetHostname(http, "localhost", 631);
  cupsHttpSetTimeout(http, 30);
  cupsHttpSetEncryption(http, HTTP_ENCRYPTION_NEVER);
  cupsHttpConnect(http);
  cupsHttpSetLogging(http, HTTP_DEBUG_LOGGING);

  ipp_t *request = ippNew();
  ippSetVersion(request, 1, 1);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "Get-Printer-Attributes",
              nullptr);
  ippAddString(request, IPP_TAG_PRINTER_URI, IPP_TAG_URI, "ipp://localhost:631/printers/MyPrinter",
              nullptr);

  cupsDoIORequest(http, request, "/printers/MyPrinter", 0, 0);
  ippDelete(request);
  cupsHttpClose(http);
  return 0;
}