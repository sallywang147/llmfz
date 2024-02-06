#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cups/cups.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  http_t *http = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption());

  if (!http) {
    return 0;
  }

  ipp_t *request = ippNewRequest(IPP_OP_GET_PRINTER_ATTRIBUTES);

  if (!request) {
    httpClose(http);
    return 0;
  }

  std::string resource = stream.ConsumeRandomLengthString();
  char *resource_ptr = const_cast<char *>(resource.c_str());

  ipp_t *response = cupsDoRequest(http, request, resource_ptr);

  if (response) {
    ippDelete(response);
  }

  httpClose(http);

  return 0;
}