#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cups/cups.h"
#include "cups/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _http_s *http = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption());
  if (http == NULL) {
    return 0;
  }

  struct _ipp_s *request = ippNew();
  if (request == NULL) {
    httpClose(http);
    return 0;
  }

  std::string resource = stream.ConsumeRandomLengthString();
  int infile = stream.ConsumeIntegral<int>();
  int outfile = stream.ConsumeIntegral<int>();

  struct _ipp_s *response = cupsDoIORequest(http, request, resource.c_str(), infile, outfile);

  ippDelete(response);
  httpClose(http);

  return 0;
}