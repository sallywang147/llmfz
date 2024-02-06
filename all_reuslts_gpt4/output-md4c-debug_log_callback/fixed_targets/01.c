#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  debug_log_callback(str1.c_str(), str2.c_str());

  return 0;
}