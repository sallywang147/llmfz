#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <stdio.h>  // For printf

int main2(int argc, char** argv) {
  printf("This is main2 function.\n");
  return 0;
}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(stream.ConsumeRemainingBytesAsString());
  }
  char** argv_ptr = new char*[argc];
  for (int i = 0; i < argc; i++) {
    argv_ptr[i] = const_cast<char*>(argv[i].c_str());
  }
  main2(argc, argv_ptr);  // Call main2 instead of main
  delete[] argv_ptr;
  return 0;
}