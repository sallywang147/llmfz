#include <ArduinoJson.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> reader(data, data + size);
  ArduinoJson::V701HB4::detail::JsonDeserializer<ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> > deserializer(reader);
  deserializer.~JsonDeserializer();
  return 0;
}