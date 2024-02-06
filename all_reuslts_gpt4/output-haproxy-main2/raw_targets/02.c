#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern int main2(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int argc = stream.ConsumeIntegralInRange<int>(0, 10);

  std::vector<char*> argv;
  for (int i = 0; i < argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    // We need to copy the string because the c_str() pointer will not be valid once 'arg' goes out of scope.
    char* arg_copy = strdup(arg.c_str());
    argv.push_back(arg_copy);
  }
  // argv must be null-terminated.
  argv.push_back(nullptr);

  main2(argc, argv.data());

  // Free the copied strings.
  for (char* arg : argv) {
    free(arg);
  }

  return 0;
}