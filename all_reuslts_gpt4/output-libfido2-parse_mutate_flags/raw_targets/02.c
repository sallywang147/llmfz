#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" void parse_mutate_flags(char * opt, int * mutate_flags);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  char *opt = const_cast<char*>(str.c_str());

  int mutate_flags = stream.ConsumeIntegral<int>();

  parse_mutate_flags(opt, &mutate_flags);

  return 0;
}