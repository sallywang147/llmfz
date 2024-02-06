#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  SerializedValue<const char*> value;
  value.size();
  return 0;
}