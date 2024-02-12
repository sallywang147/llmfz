#include <ArduinoJson.h>

extern "C" {
#include <ArduinoJson/Variant/Variant.h>
#include <ArduinoJson/Variant/VariantType.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  DynamicJsonDocument doc(4096);
  DeserializationError error = deserializeMsgPack(doc, data, size);
  if (!error) {
    std::string json;
    serializeMsgPack(doc, json);
  }
  return 0;
}