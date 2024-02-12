#include <iostream>
#include <cups/cups.h>

extern "C" {
#include <ppd/ppd.h>
}

extern "C" char * _ppdCreateFromIPP(char * buffer, size_t bufsize, struct _ipp_s * supported) {
  return ppdCreateFromIPP(buffer, bufsize, supported);
}

int main() {
  ppd_file_t *ppd = ppdCreateFromIPP(NULL);
  if (!ppd) {
    std::cerr << "Error creating PPD file." << std::endl;
    return 1;
  }

  ppdFree(ppd);
  return 0;
}