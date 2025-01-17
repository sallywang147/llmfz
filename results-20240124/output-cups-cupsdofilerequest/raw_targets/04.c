 #include "cups.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  char resource[1024];
  stream.ConsumeRandomLengthString(resource, sizeof(resource));

  char filename[1024];
  stream.ConsumeRandomLengthString(filename, sizeof(filename));

  struct _ipp_s *request = ippNewRequest(IPP_OP_PRINT_JOB);
  cupsDoFileRequest(nullptr, request, resource, filename);
  ippDelete(request);

  return 0;
}