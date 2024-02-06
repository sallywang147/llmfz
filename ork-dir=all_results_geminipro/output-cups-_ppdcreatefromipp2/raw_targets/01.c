#include <cups/cups.h>
#include <cups/ppd.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 1 || Size > 10240) {
    return 0;
  }

  FuzzedDataProvider data(Data, Size);

  size_t bufsize = data.ConsumeIntegralInRange<size_t>(1, 10240);
  char *buffer = new char[bufsize];
  memset(buffer, 0, bufsize);

  struct _ipp_s *supported = ippNew();
  struct cups_lang_s *lang = cupsLangDefault();

  char *result = _ppdCreateFromIPP2(buffer, bufsize, supported, lang);

  if (result) {
    delete[] result;
  }

  delete[] buffer;
  ippDelete(supported);

  return 0;
}