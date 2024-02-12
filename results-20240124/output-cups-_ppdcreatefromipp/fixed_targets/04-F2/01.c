#include <cups/ppd.h>

extern "C" {
#include "cups/ppd.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *buffer = new char[size + 1];
  memcpy(buffer, data, size);
  buffer[size] = '\0';

  struct _ipp_s *supported = ippNew();
  _ppdCreateFromIPP(buffer, size, supported);

  ippDelete(supported);
  delete[] buffer;

  return 0;
}