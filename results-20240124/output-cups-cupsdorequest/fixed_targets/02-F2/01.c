#include "cups/cups.h"
#include "cups/http.h"
#include "cups/ipp.h"

#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "cups/http-private.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  // Create a socket pair to simulate a connection to the printer.
  int sockets[2];
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) != 0) {
    return 0;
  }
  // Create a new HTTP connection.
  http_t *http = httpConnectEncrypt(sockets[0], HTTP_ENCRYPT_REQUIRED);
  if (http == nullptr) {
    close(sockets[0]);
    close(sockets[1]);
    return 0;
  }
  // Create a new IPP request.
  ipp_t *request = ippNew();
  if (request == nullptr) {
    httpClose(http);
    close(sockets[0]);
    close(sockets[1]);
    return 0;
  }
  // Generate a random resource name.
  std::vector<uint8_t> resource_name =
      provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange(1, 100));
  char *resource = reinterpret_cast<char*>(resource_name.data());
  // Send the IPP request to the printer.
  struct _ipp_s *response = cupsDoRequest(http, request, resource);
  // Clean up.
  ippDelete(request);
  httpClose(http);
  close(sockets[0]);
  close(sockets[1]);
  if (response != nullptr) {
    ippDelete(response);
  }
  return 0;
}