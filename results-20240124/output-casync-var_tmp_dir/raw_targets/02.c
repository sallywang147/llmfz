 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string directory_name = stream.ConsumeRemainingBytesAsString();
  char* directory_name_ptr = strdup(directory_name.c_str());
  int ret = var_tmp_dir(&directory_name_ptr);
  free(directory_name_ptr);
  return ret;
}