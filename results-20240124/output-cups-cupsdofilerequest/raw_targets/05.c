 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "ipp.h"
#include "http.h"
#include "cups.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* resource = stream.ConsumeRandomLengthString().c_str();
  const char* filename = stream.ConsumeRandomLengthString().c_str();
  const std::vector<uint8_t> request_bytes = stream.ConsumeRemainingBytes();
  ipp_t* request = ippNew();
  ippReadMem(request, request_bytes.data(), request_bytes.size());
  http_t* http = httpConnectEncrypt(nullptr, 0);
  cupsDoFileRequest(http, request, const_cast<char*>(resource), const_cast<char*>(filename));
  httpClose(http);
  ippDelete(request);
  return 0;
}