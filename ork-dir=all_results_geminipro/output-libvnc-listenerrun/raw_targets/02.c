#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" char *listenerRun(char *data);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string data_string = stream.ConsumeRemainingBytesAsString();
  char *data_ptr = const_cast<char *>(data_string.c_str());
  char *result = listenerRun(data_ptr);
  free(result);
  return 0;
}