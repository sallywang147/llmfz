#include <stddef.h>
#include <stdint.h>
#include <cups/ppd.h>
#include <cups/cups.h>
#include <cups/language.h>

extern "C" {
#include <cups/ipp.h>
}

#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz(data, size);
  char *buffer = (char *)malloc(size);
  fuzz.ReadBytes(buffer, size);
  struct _ipp_s *supported = ippNew();
  struct cups_lang_s *lang = cupsLangDefault();
  char *ppd = _ppdCreateFromIPP2(buffer, size, supported, lang);
  if (ppd) {
    free(ppd);
  }
  ippDelete(supported);
  cupsLangFree(lang);
  free(buffer);
  return 0;
}