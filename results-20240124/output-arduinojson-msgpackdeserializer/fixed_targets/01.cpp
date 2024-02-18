#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V702HB4::detail::BoundedReader<unsigned char const*, void> reader(data, size);
  ArduinoJson::detail::MsgPackDeserializer<ArduinoJson::V702HB4::detail::BoundedReader<unsigned char const*, void> > deserializer(nullptr, reader);
  deserializer.~MsgPackDeserializer();
  return 0;
}