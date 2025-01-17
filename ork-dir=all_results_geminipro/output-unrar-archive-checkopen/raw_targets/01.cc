#include <stddef.h>
#include <stdint.h>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string name = stream.ConsumeRandomLengthString(1024);
  Archive archive;
  archive.CheckOpen(&archive, reinterpret_cast<int *>(name.c_str()));

  return 0;
}