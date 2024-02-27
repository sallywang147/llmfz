#include <fuzzer/FuzzedDataProvider.h>
#include <utf8proc.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  utf8proc_unicode_version();
  return 0;
}