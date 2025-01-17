#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int main2(int argc, char **argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Generate a random number of arguments between 1 and 10.
  int argc = stream.ConsumeIntegralInRange<int>(1, 10);
  
  // Create a vector to hold the arguments.
  std::vector<std::string> argv_strings;
  for (int i = 0; i < argc; ++i) {
    argv_strings.push_back(stream.ConsumeRandomLengthString());
  }
  
  // Create the actual argv array.
  std::vector<char*> argv;
  for (auto& arg : argv_strings) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  
  // Add a null pointer at the end, as required by the argv specification.
  argv.push_back(nullptr);
  
  // Call the target function.
  main2(argc, argv.data());
  
  return 0;
}