#include <cups/cups.h>

int main() {
  ppd_file_t *ppd = ppdCreateFromIPP2("printer.ppd");
  if (!ppd) {
    // Handle error
  }

  // Use ppd

  ppdFree(ppd);

  return 0;
}