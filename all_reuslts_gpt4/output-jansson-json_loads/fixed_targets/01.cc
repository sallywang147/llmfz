#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jansson.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *json_string = const_cast<char*>(str.c_str());
  
  size_t flags = 0; // no flags set
  json_error_t error;
  
  json_t *json = json_loads(json_string, flags, &error);
  
  if(json) {
    json_decref(json);
  }
  
  return 0;
}