#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" char * packetPollLoop(char * ptr);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  std::string fuzzed_string = fuzzed_data.ConsumeRemainingBytesAsString();
  char *ptr = const_cast<char*>(fuzzed_string.c_str());

  packetPollLoop(ptr);

  return 0;
}