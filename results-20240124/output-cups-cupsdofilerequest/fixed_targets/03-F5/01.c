#include <cups/cups.h>
#include <cups/http-encrypt.h>
#include <ipp/ipp.h>

extern "C" {
struct _ipp_s * cupsDoFileRequest(struct _http_s * http, struct _ipp_s * request, char * resource, char * filename);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  httpConnectEncrypt(NULL, NULL, NULL, NULL, NULL);
  cupsDoFileRequest(NULL, NULL, NULL, NULL);
  return 0;
}