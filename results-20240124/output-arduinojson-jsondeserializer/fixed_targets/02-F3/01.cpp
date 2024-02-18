#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V702HB4::detail::BoundedReader<const unsigned char *, void> reader(const_cast<unsigned char*>(data), const_cast<unsigned char*>(data) + size);
  ArduinoJson::V702HB4::detail::JsonDeserializer<ArduinoJson::V702HB4::detail::BoundedReader<const unsigned char *, void> > deserializer(&reader, nullptr);
  deserializer.~JsonDeserializer();
  return 0;
}