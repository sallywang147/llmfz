 #include "ppd-private.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();
  char *buffer = new char[buffer_size];
  struct _ipp_s *supported = ippNew();
  _ppdCreateFromIPP(buffer, buffer_size, supported);
  delete[] buffer;
  ippDelete(supported);
  return 0;
}