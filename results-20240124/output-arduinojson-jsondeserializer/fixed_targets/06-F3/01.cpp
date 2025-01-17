#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  using namespace ArduinoJson::V702HB4;
  detail::BoundedReader<const unsigned char*, void> reader(data, size);
  detail::JsonDeserializer<detail::BoundedReader<const unsigned char*, void> > deserializer(&reader, nullptr);
  deserializer.~JsonDeserializer();
  return 0;
}