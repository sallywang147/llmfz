#include <fuzzer/FuzzedDataProvider.h>
#include <ArduinoJson.h>

using namespace ArduinoJson::V701HB4::detail;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider fuzzedDataProvider(data, size);
  
  char* ptr1 = new char[fuzzedDataProvider.ConsumeIntegralInRange<size_t>(1, size / 2)];
  char* ptr2 = new char[fuzzedDataProvider.ConsumeIntegralInRange<size_t>(1, size / 2)];

  VariantSlot::operator delete(ptr1, ptr2);

  return 0;
}