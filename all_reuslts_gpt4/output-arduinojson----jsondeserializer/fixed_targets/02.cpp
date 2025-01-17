#include <ArduinoJson.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a JsonDocument
  DynamicJsonDocument doc(1024);

  // Create a JsonDeserializer
  ArduinoJson::V701HB4::detail::JsonDeserializer<ArduinoJson::V701HB4::detail::BoundedReader<unsigned char const*, void>> deserializer(doc.memoryPool());

  // Deserialize the data
  deserializer.parse(stream.ConsumeRemainingBytesAsString());

  // Explicitly call the destructor
  deserializer.~JsonDeserializer();

  return 0;
}