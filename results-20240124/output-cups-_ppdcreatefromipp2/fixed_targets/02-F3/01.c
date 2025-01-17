extern "C" {
#include <cups/ipp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char buffer[1024];
  struct _ipp_s *supported = ippNew();
  struct cups_lang_s *lang = cupsLangDefault();
  char *ppd = _ppdCreateFromIPP2(buffer, sizeof(buffer), supported, lang);
  free(ppd);
  ippDelete(supported);
  cupsLangFree(lang);
  return 0;
}