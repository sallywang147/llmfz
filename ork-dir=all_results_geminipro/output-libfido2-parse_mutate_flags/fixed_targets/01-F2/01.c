#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <getopt.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string opt = stream.ConsumeRemainingBytesAsString();
  int mutate_flags;
  parse_mutate_flags(const_cast<char*>(opt.c_str()), &mutate_flags);
  return 0;
}

int parse_mutate_flags(char* opt, int* mutate_flags) {
  *mutate_flags = 0;
  return 0;
}