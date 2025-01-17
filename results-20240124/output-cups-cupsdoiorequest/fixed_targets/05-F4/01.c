#include <cups/cups.h>
#include <cups/http.h>
#include <cups/ipp.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <algorithm>

cups_http_t *cupsHttpNew();
const char *httpGetHostname(http_t *http, char *s, int slen);
bool httpSetEncryption(http_t *http, http_encryption_t e);
void cupsHttpSetHostname(http_t *http, const char *hostname, int port);
void cupsHttpSetTimeout(http_t *http, int timeout);
void cupsHttpConnect(http_t *http);
void cupsHttpSetLogging(http_t *http, http_log_level_t level);
ipp_attribute_t *ippAddString(ipp_t *ipp, ipp_tag_t group, ipp_tag_t value_tag, const char *name, const char *value);
ipp_t *cupsDoIORequest(http_t *http, ipp_t *request, const char *resource, int infile, int outfile);
void cupsHttpClose(http_t *http);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  http_t *http = cupsHttpNew();
  cupsHttpSetHostname(http, "localhost", 631);
  cupsHttpSetTimeout(http, 30);
  httpSetEncryption(http, HTTP_ENCRYPTION_NEVER);
  cupsHttpConnect(http);
  cupsHttpSetLogging(http, HTTP_LOG_LEVEL_DEBUG2);

  ipp_t *request = ippNew();
  ippSetVersion(request, 1, 1);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "Get-Printer-Attributes",
              nullptr);
  ippAddString(request, IPP_TAG_PRINTER, IPP_TAG_URI, "ipp://localhost:631/printers/MyPrinter",
              nullptr);

  cupsDoIORequest(http, request, "/printers/MyPrinter", 0, 0);
  ippDelete(request);
  cupsHttpClose(http);
  return 0;
}