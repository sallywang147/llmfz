#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> reader(data, size);
  ArduinoJson::V701HB4::detail::MsgPackDeserializer<ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> > deserializer(reader);
  deserializer.~MsgPackDeserializer();
  return 0;
}