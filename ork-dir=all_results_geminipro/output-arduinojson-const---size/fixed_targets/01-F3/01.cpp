#include <ArduinoJson.h>

extern "C" {
#include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, data, size);
  if (error) {
    return 0;
  }
  return 1;
}