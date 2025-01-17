#include <ArduinoJson.h>

extern "C" {
#include <ArduinoJson/Deserialization/Reader.hpp>
#include <ArduinoJson/compatibility.hpp>
#include <ArduinoJson/Namespace.hpp>
#include <ArduinoJson/Polyfills/preprocessor.hpp>

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::detail::BoundedReader<size_t> reader(data, size); // Fix: add template argument
  ArduinoJson::V702HB4::detail::JsonDeserializer<ArduinoJson::detail::BoundedReader<size_t>> deserializer(reader); // Fix: add template argument
  deserializer.read();
  return 0;
}
}