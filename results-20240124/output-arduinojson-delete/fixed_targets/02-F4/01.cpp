#include <ArduinoJson.h>
#include <stdlib.h>

extern "C" {
#include <ArduinoJson/Variant/VariantSlot.hpp>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::detail::VariantSlot* slot = new (ArduinoJson::detail::VariantSlot::operator new(sizeof(ArduinoJson::detail::VariantSlot), nullptr)) ArduinoJson::detail::VariantSlot();
  delete slot;
  return 0;
}