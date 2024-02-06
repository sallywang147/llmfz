#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" char* nts_ke_listener(char* arg);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  std::string arg = stream.ConsumeRandomLengthString();
  
  nts_ke_listener(const_cast<char*>(arg.c_str()));
  
  return 0;
}