#include <iostream>
#include <ppd/ppd.h>

extern "C" {
#include <ppd/ppd_private.h>
}

int main() {
  ppd_t *ppd = ppdCreateFromIPP2("printer.ppd");
  if (ppd == nullptr) {
    std::cerr << "Error creating PPD from IPP file." << std::endl;
    return 1;
  }

  ppdFree(ppd);
  return 0;
}