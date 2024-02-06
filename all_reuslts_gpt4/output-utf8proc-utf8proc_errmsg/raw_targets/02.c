#include <fuzzer/FuzzedDataProvider.h>
#include <utf8proc.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t errCode = stream.ConsumeIntegral<size_t>();
  utf8proc_errmsg(errCode);
  return 0;
}