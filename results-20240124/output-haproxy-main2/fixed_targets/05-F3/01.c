#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate argc and argv
  int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv(argc);
  for (int i = 0; i < argc; i++) {
    argv[i] = stream.ConsumeRemainingBytesAsString();
  }

  // Call main2
  int main2(int, char**);
  main2(argc, argv.data());

  return 0;
}
}