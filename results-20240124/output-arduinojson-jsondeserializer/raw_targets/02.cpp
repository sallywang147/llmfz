 #include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::V701HB4::detail::JsonDeserializer<ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> > deserializer;
  deserializer.~JsonDeserializer();
  return 0;
}