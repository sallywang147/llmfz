#include <ArduinoJson.h>

extern "C" {
#include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V702HB4::detail::VariantSlot::operator delete(nullptr, nullptr);
  return 0;
}