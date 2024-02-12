#include <stddef.h>
#include <stdint.h>
#include <cups/cups.h>
#include <cups/ppd.h>

extern "C" {
#include <ipp/ipp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *buffer = (char *)data;
  struct _ipp_s *supported = NULL;
  struct cups_lang_s *lang = NULL;
  char *ppd = _ppdCreateFromIPP2(buffer, size, supported, lang);
  if (ppd) {
    free(ppd);
  }
  return 0;
}