#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" void mg_hello(char * url);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string url = stream.ConsumeRemainingBytesAsString();
  mg_hello(const_cast<char*>(url.c_str()));
  return 0;
}