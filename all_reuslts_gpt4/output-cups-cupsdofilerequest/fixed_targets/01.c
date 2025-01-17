#include <cups/cups.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  http_t *http = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption());

  if (!http) {
    return 0;
  }

  ipp_t *request = ippNewRequest(CUPS_GET_DEFAULT);

  if (!request) {
    httpClose(http);
    return 0;
  }

  std::string resource = stream.ConsumeRandomLengthString();
  std::string filename = stream.ConsumeRandomLengthString();

  ipp_t *response = cupsDoFileRequest(http, request, resource.c_str(), filename.c_str());

  if (response) {
    ippDelete(response);
  }

  ippDelete(request);
  httpClose(http);

  return 0;
}