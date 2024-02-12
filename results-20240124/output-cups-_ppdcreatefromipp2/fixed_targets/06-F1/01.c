#include "cups/cups.h"

extern "C" {
#include "cups/ppd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 10) return 0;
  char buffer[1024];
  ipp_t *supported = ippNew();
  cups_lang_t *lang = cupsLangDefault();
  _ppdCreateFromIPP2(buffer, sizeof(buffer), supported, lang);
  ippDelete(supported);
  return 0;
}