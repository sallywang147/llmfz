#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize argc and argv.
  int argc = 1;
  std::vector<char*> argv;
  argv.push_back(const_cast<char*>("main262"));

  // Parse the input data as command-line arguments.
  while (provider.remaining_bytes() > 0) {
    std::string arg = provider.ConsumeRemainingBytesAsString();
    argv.push_back(const_cast<char*>(arg.c_str()));
    argc++;
  }

  // Call main262 with the parsed arguments.
  int result = main262(argc, argv.data());

  // Clean up the argv array.
  for (int i = 1; i < argc; i++) {
    free(argv[i]);
  }

  return result;
}