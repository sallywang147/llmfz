#include <stddef.h>
#include <stdint.h>
#include <cups/cups.h>
#include <cups/ppd.h>

extern "C" {
#include <ipp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  cups_lang_s lang;
  char *ppd = _ppdCreateFromIPP2((char *)data, size, NULL, &lang);
  free(ppd);
  return 0;
}