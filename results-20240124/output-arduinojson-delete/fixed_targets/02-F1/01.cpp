#include <ArduinoJson.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::VariantSlot* slot = new ArduinoJson::VariantSlot();
  delete slot;
  return 0;
}