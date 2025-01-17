#include <iostream>
#include <cups/cups.h>

extern "C" {
#include <ppd/ppd.h>
}

extern "C" char * _ppdCreateFromIPP(char * buffer, size_t bufsize, struct _ipp_s * supported);

int main() {
  char *buffer = nullptr;
  size_t bufsize = 0;
  struct _ipp_s *supported = nullptr;
  ppd_file_t *ppd = _ppdCreateFromIPP(buffer, bufsize, supported);
  if (ppd == NULL) {
    std::cerr << "Error creating PPD file." << std::endl;
    return 1;
  }
  ppdFree(ppd);
  return 0;
}