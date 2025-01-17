#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  using namespace ArduinoJson::V702HB4;
  detail::BoundedReader<unsigned char const*, void> reader(data, size);
  detail::JsonDeserializer<detail::BoundedReader<unsigned char const*, void> > deserializer(reader);
  deserializer.~JsonDeserializer();
  return 0;
}