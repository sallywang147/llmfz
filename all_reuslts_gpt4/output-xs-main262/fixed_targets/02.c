#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // The first argument is always the program name
  std::vector<char*> argv = {strdup("fuzzer")};
  while (stream.remaining_bytes() > 0) {
    std::string arg = stream.ConsumeRandomLengthString();
    if (arg.empty()) {
      continue;
    }
    argv.push_back(strdup(arg.c_str()));
  }

  // Add a null pointer at the end of argv as required by the exec functions
  argv.push_back(nullptr);

  int argc = argv.size() - 1;

  // Call the function to fuzz
  main262(argc, argv.data());

  // Free the allocated strings
  for (char* arg : argv) {
    free(arg);
  }

  return 0;
}