#include "cups/cups.h"

extern "C" int
LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  char filename[256];
  sprintf(filename, "/tmp/libfuzzer.%d", getpid());
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }

  fwrite(Data, Size, 1, fp);
  fclose(fp);

  struct _http_s *http = httpConnectEncrypt(cupsServer(), 631, 0);
  if (!http) {
    return 0;
  }

  struct _ipp_s *request = ippNewRequest(IPP_GET_JOBS);
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "Print-Job", NULL);

  cupsDoFileRequest(http, request, "/jobs", filename);

  ippDelete(request);
  httpClose(http);

  unlink(filename);

  return 0;
}