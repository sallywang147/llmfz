#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V702HB4::detail::BoundedReader<unsigned char const*, void> reader(data, size);
  ArduinoJson::detail::ResourceManager resources;
  ArduinoJson::detail::JsonDeserializer<ArduinoJson::V702HB4::detail::BoundedReader<unsigned char const*, void> > deserializer(&resources, &reader);
  deserializer.~JsonDeserializer();
  return 0;
}