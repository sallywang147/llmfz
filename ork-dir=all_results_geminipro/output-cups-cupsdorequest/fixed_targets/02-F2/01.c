#include <cups/cups.h>
#include <cups/ipp.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider fdp(Data, Size);

  // Create a new HTTP connection.
  http_t *http = httpConnectEncrypt(nullptr, 0);
  if (!http) {
    return 0;
  }

  // Create a new IPP request.
  ipp_t *request = ippNewRequest(IPP_VERSION_1_1);
  if (!request) {
    httpClose(http);
    return 0;
  }

  // Generate a random resource string.
  const size_t resource_length = fdp.ConsumeIntegralInRange<size_t>(0, 1024);
  char *resource = new char[resource_length + 1];
  fdp.ConsumeBytes<char>(resource, resource_length);
  resource[resource_length] = '\0';

  // Send the IPP request to the server.
  ipp_t *response = cupsDoRequest(http, request, resource);

  // Clean up.
  ippDelete(request);
  ippDelete(response);
  httpClose(http);
  delete[] resource;

  return 0;
}