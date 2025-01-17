#include <cups/cups.h>
#include <cups/ppd.h>

extern "C" {
#include "ppd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ppd_file_t *ppd = ppdCreateFromIPP2((char *)data, size, NULL, NULL);
  if (!ppd) {
    return 0;
  }
  ppdFree(ppd);
  return 0;
}

int main() {
  return 0;
}