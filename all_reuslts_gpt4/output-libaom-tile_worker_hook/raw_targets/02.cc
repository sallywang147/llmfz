#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int tile_worker_hook(char * , char * );

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    // Not enough data for fuzzing.
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(1, size / 2));
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  tile_worker_hook(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));

  return 0;
}