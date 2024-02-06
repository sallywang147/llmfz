#include <fuzzer/FuzzedDataProvider.h>
#include <cstring>
#include <string>

extern "C" {
#include <mongoose.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string url = stream.ConsumeRemainingBytesAsString();
  mg_hello(const_cast<char*>(url.c_str()));
  return 0;
}