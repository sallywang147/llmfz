 #include <cups/cups.h>
#include <cups/ppd.h>
#include <cups/ipp.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *buffer = stream.ConsumeRemainingBytesAsString().c_str();
  size_t bufsize = stream.ConsumeIntegralInRange(1, 1024);
  struct _ipp_s *supported = ippNew();

  char *ppd = _ppdCreateFromIPP(buffer, bufsize, supported);

  ippDelete(supported);
  free(ppd);

  return 0;
}