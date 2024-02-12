#include <ArduinoJson.h>

extern "C" {
#include <stdlib.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ArduinoJson::Variant v;
  ::operator delete(v.ptr, v.ptr);
  return 0;
}