#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int main2(int argc, char **argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data to create argc and argv
  int argc = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<std::string> argv_strings;
  std::vector<char*> argv;

  // Create argv from the fuzzing data
  for (int i = 0; i < argc; ++i) {
    argv_strings.push_back(stream.ConsumeRandomLengthString());
  }

  // Convert vector of strings to vector of char*
  for (auto& str : argv_strings) {
    argv.push_back(const_cast<char*>(str.c_str()));
  }

  // Call the target function
  main2(argc, argv.data());

  return 0;
}