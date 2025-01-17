#include "cups.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "./../cups/http.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int infile = stream.ConsumeIntegral<int>();
  const int outfile = stream.ConsumeIntegral<int>();
  const char* resource = stream.ConsumeRandomLengthString().c_str();
  struct _ipp_s *request = ippNew();
  struct _http_s *http = httpConnectEncrypt(nullptr, 0, HTTP_ENCRYPT_NEVER);
  cupsDoIORequest(http, request, const_cast<char*>(resource), infile, outfile);
  ippDelete(request);
  httpClose(http);
  return 0;
}