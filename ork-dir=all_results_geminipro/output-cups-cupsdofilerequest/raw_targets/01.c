#include "cups/cups.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  // Create a temporary file to store the input data.
  std::string tmpfile = std::tmpnam(nullptr);
  FILE* f = fopen(tmpfile.c_str(), "wb");
  if (f == nullptr) {
    return 0;
  }
  fwrite(data, size, 1, f);
  fclose(f);

  // Create a new HTTP connection.
  http_t* http = httpConnectEncrypt(nullptr, 0);
  if (http == nullptr) {
    return 0;
  }

  // Create an IPP request.
  ipp_t* request = ippNewRequest(IPP_VERSION_1_1);
  if (request == nullptr) {
    httpClose(http);
    return 0;
  }

  // Set the IPP request's operation.
  ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_NAME, "Print-Job");

  // Set the IPP request's destination printer.
  ippAddString(request, IPP_TAG_PRINTER, IPP_TAG_NAME, "MyPrinter");

  // Set the IPP request's document name.
  ippAddString(request, IPP_TAG_DOCUMENT_NAME, IPP_TAG_NAME, "MyDocument");

  // Set the IPP request's document format.
  ippAddString(request, IPP_TAG_DOCUMENT_FORMAT, IPP_TAG_MIMETYPE, "application/pdf");

  // Set the IPP request's document data.
  ippAddString(request, IPP_TAG_DOCUMENT_DATA, IPP_TAG_NAME, tmpfile.c_str());

  // Send the IPP request to the printer.
  ipp_t* response = cupsDoFileRequest(http, request, "/printers/MyPrinter", tmpfile.c_str());

  // Clean up.
  ippDelete(request);
  ippDelete(response);
  httpClose(http);
  unlink(tmpfile.c_str());

  return 0;
}