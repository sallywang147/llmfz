#include <iostream>
#include <cups/cups.h>

extern "C" {
#include <ppd/ppd.h>
}

extern "C" char * _ppdCreateFromIPP2(char * buffer, size_t bufsize, struct _ipp_s * supported, struct cups_lang_s * lang) {
  return ppdCreateFromIPP2(buffer, bufsize, supported, lang);
}

int main() {
  ppd_file_t *ppd = ppdCreateFromIPP2(NULL, NULL);
  if (!ppd) {
    std::cerr << "Error creating PPD file." << std::endl;
    return 1;
  }

  ppdFree(ppd);
  return 0;
}