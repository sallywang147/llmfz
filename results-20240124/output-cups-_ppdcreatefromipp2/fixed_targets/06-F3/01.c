#include <cups/cups.h>
#include <cups/ppd.h>

extern "C" {
#include "ppd.h"
}

int main() {
  ppd_file_t *ppd = ppdCreateFromIPP2("printer.ppd");
  if (!ppd) {
    return 1;
  }
  ppdFree(ppd);
  return 0;
}