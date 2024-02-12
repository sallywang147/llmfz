#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <vector>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int arg_count = stream.ConsumeIntegral<int>();
  std::vector<char*> arg_list;
  arg_list.push_back((char*)"");
  for (int i = 0; i < arg_count; ++i) {
    std::string arg = stream.ConsumeRemainingBytesAsString();
    char* arg_ptr = (char*)malloc(arg.size() + 1);
    memcpy(arg_ptr, arg.c_str(), arg.size());
    arg_ptr[arg.size()] = '\0';
    arg_list.push_back(arg_ptr);
  }
  char** arg_array = &arg_list[0];
  int result = main(arg_count + 1, arg_array);
  for (int i = 1; i < arg_count + 1; ++i) {
    free(arg_array[i]);
  }
  return result;
}