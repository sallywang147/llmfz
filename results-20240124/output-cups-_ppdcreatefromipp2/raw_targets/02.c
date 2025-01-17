 #include <cups/cups.h>
#include <cups/ppd.h>
#include <cups/language.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();
  char *buffer = static_cast<char*>(malloc(buffer_size));
  const struct ipp_s *supported = stream.ConsumeBool()
                                      ? ippNew()
                                      : reinterpret_cast<ipp_t*>(nullptr);
  const struct cups_lang_s *lang = stream.ConsumeBool()
                                       ? cupsLangDefault()
                                       : reinterpret_cast<cups_lang_t*>(nullptr);
  char *ppd = _ppdCreateFromIPP2(buffer, buffer_size,
                                 const_cast<struct ipp_s*>(supported),
                                 const_cast<struct cups_lang_s*>(lang));
  free(ppd);
  if (supported) {
    ippDelete(const_cast<struct ipp_s*>(supported));
  }
  free(buffer);
  return 0;
}