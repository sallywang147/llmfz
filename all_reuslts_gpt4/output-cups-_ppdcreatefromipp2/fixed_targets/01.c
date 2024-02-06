#include <fuzzer/FuzzedDataProvider.h>
#include <cups/cups.h>
#include <cups/ipp.h>
#include <cups/ppd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _ipp_s *supported = ippNew();
  struct cups_lang_s *lang = cupsLangDefault();

  std::vector<char> buffer = stream.ConsumeBytes<char>(stream.remaining_bytes());

  char* result = _ppdCreateFromIPP2(buffer.data(), buffer.size(), supported, lang);

  ippDelete(supported);
  cupsLangFree(lang);

  return 0;
}