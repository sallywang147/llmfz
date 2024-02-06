#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

int main2(int argc, char** argv) {
  printf("argc: %zu\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<char*> argv;
  argv.push_back((char*)"program_name");

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    std::string arg_str = provider.ConsumeRandomLengthString(arg_size);
    argv.push_back((char*)arg_str.c_str());
  }

  int argc = argv.size();
  char** argv_ptr = argv.data();
  main2(argc, argv_ptr);

  return 0;
}