#include <ArduinoJson.h>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V702HB4::detail::VariantSlot* slot = new (ArduinoJson::V702HB4::detail::VariantSlot::operator new) ArduinoJson::V702HB4::detail::VariantSlot;
  delete slot;
  return 0;
}
}