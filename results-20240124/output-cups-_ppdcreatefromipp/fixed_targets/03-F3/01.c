#include <cups/cups.h>

extern "C" {
#include <cups/ppd.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *buffer = new char[size];
  memcpy(buffer, data, size);

  struct _ipp_s *supported = ippNew();
  _ppdCreateFromIPP(buffer, size, supported);

  ippDelete(supported);
  delete[] buffer;
  return 0;
}