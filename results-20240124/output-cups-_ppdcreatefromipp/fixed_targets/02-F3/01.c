#include <iostream>
#include <cups/cups.h>

extern "C" {
#include <ppd/ppd.h>
}

int main() {
  ppd_file_t *ppd = ppdCreateFromIPP(NULL, NULL);
  if (ppd == NULL) {
    std::cerr << "Error creating PPD file." << std::endl;
    return 1;
  }
  ppdFree(ppd);
  return 0;
}