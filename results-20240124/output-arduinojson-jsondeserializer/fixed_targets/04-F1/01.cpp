#include <ArduinoJson.h>

extern "C" {
#include <ArduinoJson/Deserialization/Reader.hpp>
#include <ArduinoJson/compatibility.hpp>
#include <ArduinoJson/Namespace.hpp>
#include <ArduinoJson/Polyfills/preprocessor.hpp>

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  BoundedReader reader(data, size);
  ArduinoJson::V702HB4::detail::JsonDeserializer<BoundedReader> deserializer(reader);
  deserializer.read();
  return 0;
}
}