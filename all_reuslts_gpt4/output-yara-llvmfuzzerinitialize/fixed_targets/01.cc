#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize argc and argv
  int argc = stream.ConsumeIntegral<int>();
  char** argv = new char*[argc];

  for (int i = 0; i < argc; i++) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv[i] = new char[arg.size() + 1];
    std::copy(arg.begin(), arg.end(), argv[i]);
    argv[i][arg.size()] = '\0';  // Null-terminate the string
  }

  // Call the function to fuzz
  LLVMFuzzerInitialize(&argc, &argv);

  // Cleanup
  for (int i = 0; i < argc; i++) {
    delete[] argv[i];
  }
  delete[] argv;

  return 0;
}