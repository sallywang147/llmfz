 #include "cups/cups.h"
#include "cups/ppd.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);
  char *buffer = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 1024));
  size_t bufsize = stream.ConsumeIntegralInRange(0, 1024);
  struct _ipp_s *supported = stream.PickValueInArray({nullptr, ippNew(), ippNewRequest()});
  struct cups_lang_s *lang = stream.PickValueInArray({nullptr, cupsLangDefault()});

  _ppdCreateFromIPP2(buffer, bufsize, supported, lang);

  if (supported != nullptr) {
    ippDelete(supported);
  }
  return 0;
}