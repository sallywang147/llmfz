#include <cups/cups.h>
#include <cups/ipp.h>
#include <cups/ppd.h>
#include <cups/string.h>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <cups/ppd.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(
      100, 100000);
  char* buffer = new char[buffer_size];
  memset(buffer, 0, buffer_size);
  const size_t supported_size = stream.ConsumeIntegralInRange<size_t>(
      100, 100000);
  char* supported = new char[supported_size];
  memset(supported, 0, supported_size);
  const size_t lang_size = stream.ConsumeIntegralInRange<size_t>(
      100, 100000);
  char* lang = new char[lang_size];
  memset(lang, 0, lang_size);
  char* result = _ppdCreateFromIPP2(buffer, buffer_size,
                                     (ipp_t*)supported, (cups_lang_t*)lang);
  delete[] buffer;
  delete[] supported;
  delete[] lang;
  delete[] result;
  return 0;
}