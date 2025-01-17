#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Uri.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct UriUriStructW uri_struct;
  int first_non_uri_char;
  int chars_required;
  int* error_pos = nullptr;
  
  std::vector<uint16_t> wide_string = stream.ConsumeRemainingBytes<uint16_t>();
  if(wide_string.empty()){
    return 0;
  }
  
  int result = uriParseSingleUriExW(&uri_struct, wide_string.data(), &first_non_uri_char, &chars_required, &error_pos);
  
  uriFreeUriMembersW(&uri_struct);
  
  return 0;
}