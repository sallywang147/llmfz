#include <fuzzer/FuzzedDataProvider.h>
#include <ArduinoJson.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRandomLengthString();
  ArduinoJson::SerializedValue<const char*> serializedValue(str.c_str());
  size_t valueSize = serializedValue.size();
  return 0;
}