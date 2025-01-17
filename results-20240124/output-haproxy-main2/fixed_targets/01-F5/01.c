#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <unistd.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int arg_count = stream.ConsumeIntegral<int>();
  const std::string program_name = stream.ConsumeRandomLengthString();
  std::vector<std::string> args;
  for (int i = 0; i < arg_count; i++) {
    args.push_back(stream.ConsumeRandomLengthString());
  }
  int argc = arg_count + 1;
  char** argv = new char*[argc];
  argv[0] = const_cast<char*>(program_name.c_str());
  for (int i = 1; i < argc; i++) {
    argv[i] = const_cast<char*>(args[i - 1].c_str());
  }
  int (*main_func)(int, char**) = (int (*)(int, char**))main;  // Change main2 to main
  main_func(argc, argv);
  delete[] argv;
  return 0;
}