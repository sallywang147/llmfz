#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int tile_worker_hook(char *, char *);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeRandomLengthString();
  char *ptr1 = const_cast<char*>(str1.c_str());

  std::string str2 = stream.ConsumeRemainingBytesAsString();
  char *ptr2 = const_cast<char*>(str2.c_str());

  tile_worker_hook(ptr1, ptr2);

  return 0;
}