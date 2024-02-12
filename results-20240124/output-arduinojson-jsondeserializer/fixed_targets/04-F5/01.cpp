#include <ArduinoJson.h>

extern "C" {
#include <ArduinoJson/Deserialization/Reader.hpp>
#include <ArduinoJson/compatibility.hpp>
#include <ArduinoJson/Namespace.hpp>
#include <ArduinoJson/Polyfills/preprocessor.hpp>

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  using namespace ArduinoJson::V702HB4;
  using namespace ArduinoJson::detail;
  BoundedReader<size_t> reader(data, size);
  JsonDeserializer<BoundedReader<size_t>> deserializer(reader);
  deserializer.read();
  return 0;
}
}