#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

extern "C" {
#include "http.h"
#include "ipp-private.h"
#include "string-private.h"
}

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *resource = stream.ConsumeBytesAsString().c_str();
  char *filename = stream.ConsumeBytesAsString().c_str();
  int infile = stream.ConsumeIntegral<int>();
  int outfile = stream.ConsumeIntegral<int>();

  struct _http_s *http = httpNew();
  struct _ipp_s *request = ippNew();

  ippReadFile(filename, request);

  struct _ipp_s *response = cupsDoIORequest(http, request, resource, infile, outfile);

  ippDelete(request);
  ippDelete(response);
  httpFree(http);

  return 0;
}