 #include "cups/cups.h"
#include "cups/ppd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t bufsize = stream.ConsumeIntegral<size_t>();
  char *buffer = new char[bufsize];
  const size_t ipp_size = stream.ConsumeIntegral<size_t>();
  const uint8_t *ipp_data = stream.ConsumeBytes<uint8_t>(ipp_size);
  ipp_t *supported = ippNew();
  ippReadMem(supported, ipp_data, ipp_size);

  char *ppd = _ppdCreateFromIPP(buffer, bufsize, supported);
  if (ppd) {
    delete[] ppd;
  }
  delete[] buffer;
  ippDelete(supported);
  return 0;
}