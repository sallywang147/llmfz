#include <fuzzer/FuzzedDataProvider.h>
#include <json.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();

  json_object *obj = json_tokener_parse(const_cast<char*>(str.c_str()));

  if (obj != nullptr) {
    (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);
    json_object_put(obj);
  }

  return 0;
}