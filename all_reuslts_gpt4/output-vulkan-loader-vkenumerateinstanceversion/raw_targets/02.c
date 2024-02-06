#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int version;
  vkEnumerateInstanceVersion(&version);

  return 0;
}