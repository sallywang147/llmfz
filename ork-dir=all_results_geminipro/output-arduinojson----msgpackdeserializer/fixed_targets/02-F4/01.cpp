#include <ArduinoJson.h>

extern "C" {
#include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> reader(data, size);
  ArduinoJson::V701HB4::detail::MsgPackDeserializer<ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> > deserializer(reader);
  deserializer.~MsgPackDeserializer();  // Fix: Use the correct destructor syntax
  return 0;
}