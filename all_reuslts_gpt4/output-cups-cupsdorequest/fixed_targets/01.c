#include <cups/cups.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a HTTP connection
  http_t *http = httpConnectEncrypt(cupsServer(), ippPort(), cupsEncryption());

  // Create an IPP request
  ipp_t *request = ippNewRequest(IPP_OP_GET_PRINTER_ATTRIBUTES);

  // Extract a string for resource
  std::string resource = stream.ConsumeRandomLengthString();
  
  // Call the function to fuzz
  ipp_t *response = cupsDoRequest(http, request, resource.c_str());

  // Cleanup
  if(response) {
    ippDelete(response);
  }

  httpClose(http);

  return 0;
}