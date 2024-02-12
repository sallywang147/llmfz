#include <ArduinoJson.h>
#include <ArduinoJson/MsgPack/MsgPackDeserializer.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V702HB4::detail::BoundedReader<const unsigned char*, void> reader(data, size);
  ArduinoJson::V702HB4::detail::MsgPackDeserializer<ArduinoJson::V702HB4::detail::BoundedReader<const unsigned char*, void> > deserializer(reader);
  deserializer.~MsgPackDeserializer();
  return 0;
}