#include <ArduinoJson.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> reader(stream.ConsumeRemainingBytes<unsigned char>().data(), size);
  ArduinoJson::V701HB4::detail::JsonDeserializer<ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void> > deserializer(reader);

  // Explicitly call the destructor
  deserializer.~JsonDeserializer();

  return 0;
}