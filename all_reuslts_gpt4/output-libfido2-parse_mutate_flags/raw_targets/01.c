#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern void parse_mutate_flags(char * opt, int * mutate_flags);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string opt = stream.ConsumeRandomLengthString();
  int mutate_flags = 0;

  parse_mutate_flags(const_cast<char*>(opt.c_str()), &mutate_flags);

  return 0;
}