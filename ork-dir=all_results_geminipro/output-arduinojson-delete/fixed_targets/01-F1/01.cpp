#include <ArduinoJson.h>

extern "C" {
#include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ArduinoJson::V701HB4::detail::VariantSlot* slot =
      new ArduinoJson::V701HB4::detail::VariantSlot;
  delete slot;
  return 0;
}