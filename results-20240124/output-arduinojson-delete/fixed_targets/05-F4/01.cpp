#include <ArduinoJson.h>
#include <stdlib.h>

extern "C" {
#include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::DeserializationError error;
  ArduinoJson::parse(v, (const char*)data, size, error);
  ::operator delete(v.ptr, v.ptr);
  return 0;
}