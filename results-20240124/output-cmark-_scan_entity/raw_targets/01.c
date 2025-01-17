 #include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string str = stream.ConsumeRemainingBytesAsString();
  char* c_str = const_cast<char*>(str.c_str());
  _scan_entity(c_str);
  return 0;
}