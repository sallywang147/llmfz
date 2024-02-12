#include <ArduinoJson.h>
#include <ArduinoJson/MsgPack/MsgPackDeserializer.hpp>

extern "C" {
#include <ArduinoJson/detail/ResourceManager.hpp>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V702HB4::detail::BoundedReader<unsigned char const*, void> reader(
      data, size);
  ArduinoJson::V702HB4::detail::MsgPackDeserializer<
      ArduinoJson::V702HB4::detail::BoundedReader<unsigned char const*, void> >
      deserializer(ArduinoJson::detail::ResourceManager::getInstance(),
                   reader);
  deserializer.~MsgPackDeserializer();
  return 0;
}